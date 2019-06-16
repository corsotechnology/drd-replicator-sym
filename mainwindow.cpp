#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionFull_screen,SIGNAL(triggered()),this,SLOT(Full_screen()));
    //--Projects database
    db = QSqlDatabase::addDatabase("QSQLITE","MASTER-"+QVariant(rand()+rand()).toString());
    db.setDatabaseName("projects.db");
    if (!db.open())
       {
          QMessageBox::information(this,"Projects DB-Error",db.lastError().text());
          close();
       }
    channel_manager = new QNetworkAccessManager();
    connect(channel_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(channel_managerFinished(QNetworkReply*)));
    node_manager = new QNetworkAccessManager();
    connect(node_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(node_managerFinished(QNetworkReply*)));
    node_group_manager = new QNetworkAccessManager();
    connect(node_group_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(node_group_managerFinished(QNetworkReply*)));
    node_group_link_manager = new QNetworkAccessManager();
    connect(node_group_link_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(node_group_link_managerFinished(QNetworkReply*)));
    router_manager = new QNetworkAccessManager();
    connect(router_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(router_managerFinished(QNetworkReply*)));
    trigger_manager = new QNetworkAccessManager();
    connect(trigger_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(trigger_managerFinished(QNetworkReply*)));
    trigger_router_manager = new QNetworkAccessManager();
    connect(trigger_router_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(trigger_router_managerFinished(QNetworkReply*)));
    notification_manager = new QNetworkAccessManager();
    connect(notification_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(notification_managerFinished(QNetworkReply*)));
    monitor_manager = new QNetworkAccessManager();
    connect(monitor_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(monitor_managerFinished(QNetworkReply*)));
    parameter_manager = new QNetworkAccessManager();
    connect(parameter_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(parameter_managerFinished(QNetworkReply*)));
    req_manager = new QNetworkAccessManager();
    connect(req_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(req_managerFinished(QNetworkReply*)));
    completer_manager = new QNetworkAccessManager();
    connect(completer_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(completer_managerFinished(QNetworkReply*)));
    //-Administration managers
    ch_status_manager = new QNetworkAccessManager();
    connect(ch_status_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(ch_status_managerFinished(QNetworkReply*)));
    out_bt_manager = new QNetworkAccessManager();
    connect(out_bt_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(out_bt_managerFinished(QNetworkReply*)));
    in_bt_manager = new QNetworkAccessManager();
    connect(in_bt_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(in_bt_managerFinished(QNetworkReply*)));
    child_out_bt_manager = new QNetworkAccessManager();
    connect(child_out_bt_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(child_out_bt_managerFinished(QNetworkReply*)));
    child_in_bt_manager = new QNetworkAccessManager();
    connect(child_in_bt_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(child_in_bt_managerFinished(QNetworkReply*)));
    query_db_manager = new QNetworkAccessManager();
    connect(query_db_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(query_db_managerFinished(QNetworkReply*)));
    out_metrics_manager = new QNetworkAccessManager();
    connect(out_metrics_manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(out_metrics_managerFinished(QNetworkReply*)));

    //--------------
    connect(ui->actionConfiguration,SIGNAL(triggered()),this,SLOT(Display_configuration()));
    connect(ui->actionAdminnistration,SIGNAL(triggered()),this,SLOT(Display_administration()));
    //--Config actions
    QAction *add_ch = new QAction(this);
    add_ch->setText("Add channel");
    connect(add_ch, &QAction::triggered, this, &MainWindow::add_channel);
    ui->tableView_channel->addAction(add_ch);

    QAction *mod_ch = new QAction(this);
    mod_ch->setText("Modify channel");
    connect(mod_ch, &QAction::triggered, this, &MainWindow::modify_channel);
    ui->tableView_channel->addAction(mod_ch);

    QAction *rem_ch = new QAction(this);
    rem_ch->setText("Remove channel");
    connect(rem_ch, &QAction::triggered, this, &MainWindow::remove_channel);
    ui->tableView_channel->addAction(rem_ch);

    QAction *refresh_ch = new QAction(this);
    refresh_ch->setText("Refresh list");
    connect(refresh_ch, &QAction::triggered, this, &MainWindow::refresh_channel);
    ui->tableView_channel->addAction(refresh_ch);
    //-
    QAction *refsesh_nd = new QAction(this);
    refsesh_nd->setText("Refresh list");
    connect(refsesh_nd, &QAction::triggered, this, &MainWindow::refresh_node);
    ui->tableView_node->addAction(refsesh_nd);
    //-
    QAction *add_ndgr = new QAction(this);
    add_ndgr->setText("Add node group");
    connect(add_ndgr, &QAction::triggered, this, &MainWindow::add_node_group);
    ui->tableView_node_group->addAction(add_ndgr);

    QAction *mod_ndgr = new QAction(this);
    mod_ndgr->setText("Modify node group");
    connect(mod_ndgr, &QAction::triggered, this, &MainWindow::modify_node_group);
    ui->tableView_node_group->addAction(mod_ndgr);

    QAction *rem_ndgr = new QAction(this);
    rem_ndgr->setText("Remove node group");
    connect(rem_ndgr, &QAction::triggered, this, &MainWindow::remove_node_group);
    ui->tableView_node_group->addAction(rem_ndgr);

    QAction *refresh_ndgr = new QAction(this);
    refresh_ndgr->setText("Refresh list");
    connect(refresh_ndgr, &QAction::triggered, this, &MainWindow::refresh_node_group);
    ui->tableView_node_group->addAction(refresh_ndgr);
    //-
    QAction *add_ndgrlnk = new QAction(this);
    add_ndgrlnk->setText("Add node group link");
    connect(add_ndgrlnk, &QAction::triggered, this, &MainWindow::add_node_group_link);
    ui->tableView_node_group_link->addAction(add_ndgrlnk);

    QAction *mod_ndgrlnk = new QAction(this);
    mod_ndgrlnk->setText("Modify node group link");
    connect(mod_ndgrlnk, &QAction::triggered, this, &MainWindow::modify_node_group_link);
    ui->tableView_node_group_link->addAction(mod_ndgrlnk);

    QAction *rem_ndgrlnk = new QAction(this);
    rem_ndgrlnk->setText("Remove node group link");
    connect(rem_ndgrlnk, &QAction::triggered, this, &MainWindow::remove_node_group_link);
    ui->tableView_node_group_link->addAction(rem_ndgrlnk);

    QAction *refresh_ndgrlnk = new QAction(this);
    refresh_ndgrlnk->setText("Refresh list");
    connect(refresh_ndgrlnk, &QAction::triggered, this, &MainWindow::refresh_node_group_link);
    ui->tableView_node_group_link->addAction(refresh_ndgrlnk);
    //-
    QAction *add_rt = new QAction(this);
    add_rt->setText("Add router");
    connect(add_rt, &QAction::triggered, this, &MainWindow::add_router);
    ui->tableView_router->addAction(add_rt);

    QAction *mod_rt = new QAction(this);
    mod_rt->setText("Modify router");
    connect(mod_rt, &QAction::triggered, this, &MainWindow::modify_router);
    ui->tableView_router->addAction(mod_rt);

    QAction *rem_rt = new QAction(this);
    rem_rt->setText("Remove router");
    connect(rem_rt, &QAction::triggered, this, &MainWindow::remove_router);
    ui->tableView_router->addAction(rem_rt);

    QAction *refresh_rt = new QAction(this);
    refresh_rt->setText("Refresh list");
    connect(refresh_rt, &QAction::triggered, this, &MainWindow::refresh_router);
    ui->tableView_router->addAction(refresh_rt);
    //-
    QAction *add_tr = new QAction(this);
    add_tr->setText("Add trigger");
    connect(add_tr, &QAction::triggered, this, &MainWindow::add_trigger);
    ui->tableView_trigger->addAction(add_tr);

    QAction *mod_tr = new QAction(this);
    mod_tr->setText("Modify trigger");
    connect(mod_tr, &QAction::triggered, this, &MainWindow::modify_trigger);
    ui->tableView_trigger->addAction(mod_tr);

    QAction *rem_tr = new QAction(this);
    rem_tr->setText("Remove trigger");
    connect(rem_tr, &QAction::triggered, this, &MainWindow::remove_trigger);
    ui->tableView_trigger->addAction(rem_tr);

    QAction *refresh_tr = new QAction(this);
    refresh_tr->setText("Refresh list");
    connect(refresh_tr, &QAction::triggered, this, &MainWindow::refresh_trigger);
    ui->tableView_trigger->addAction(refresh_tr);
    //-
    QAction *add_trrt = new QAction(this);
    add_trrt->setText("Add trigger router");
    connect(add_trrt, &QAction::triggered, this, &MainWindow::add_trigger_router);
    ui->tableView_trigger_router->addAction(add_trrt);

    QAction *mod_trrt = new QAction(this);
    mod_trrt->setText("Modify trigger router");
    connect(mod_trrt, &QAction::triggered, this, &MainWindow::modify_trigger_router);
    ui->tableView_trigger_router->addAction(mod_trrt);

    QAction *rem_trrt = new QAction(this);
    rem_trrt->setText("Remove trigger router");
    connect(rem_trrt, &QAction::triggered, this, &MainWindow::remove_trigger_router);
    ui->tableView_trigger_router->addAction(rem_trrt);

    QAction *refresh_trrt = new QAction(this);
    refresh_trrt->setText("Refresh list");
    connect(refresh_trrt, &QAction::triggered, this, &MainWindow::refresh_trigger_router);
    ui->tableView_trigger_router->addAction(refresh_trrt);
    //-
    QAction *add_not = new QAction(this);
    add_not->setText("Add notification");
    connect(add_not, &QAction::triggered, this, &MainWindow::add_notification);
    ui->tableView_notification->addAction(add_not);

    QAction *mod_not = new QAction(this);
    mod_not->setText("Modify notification");
    connect(mod_not, &QAction::triggered, this, &MainWindow::modify_notification);
    ui->tableView_notification->addAction(mod_not);

    QAction *rem_not = new QAction(this);
    rem_not->setText("Remove notification");
    connect(rem_not, &QAction::triggered, this, &MainWindow::remove_notification);
    ui->tableView_notification->addAction(rem_not);

    QAction *refresh_not = new QAction(this);
    refresh_not->setText("Refresh list");
    connect(refresh_not, &QAction::triggered, this, &MainWindow::refresh_notification);
    ui->tableView_notification->addAction(refresh_not);
    //-
    QAction *add_mon = new QAction(this);
    add_mon->setText("Add monitor");
    connect(add_mon, &QAction::triggered, this, &MainWindow::add_monitor);
    ui->tableView_monitor->addAction(add_mon);

    QAction *mod_mon = new QAction(this);
    mod_mon->setText("Modify monitor");
    connect(mod_mon, &QAction::triggered, this, &MainWindow::modify_monitor);
    ui->tableView_monitor->addAction(mod_mon);

    QAction *rem_mon = new QAction(this);
    rem_mon->setText("Remove monitor");
    connect(rem_mon, &QAction::triggered, this, &MainWindow::remove_monitor);
    ui->tableView_monitor->addAction(rem_mon);

    QAction *refresh_mon = new QAction(this);
    refresh_mon->setText("Refresh list");
    connect(refresh_mon, &QAction::triggered, this, &MainWindow::refresh_monitor);
    ui->tableView_monitor->addAction(refresh_mon);
    //-
    QAction *add_par = new QAction(this);
    add_par->setText("Add parameter");
    connect(add_par, &QAction::triggered, this, &MainWindow::add_parameter);
    ui->tableView_parameter->addAction(add_par);

    QAction *mod_par = new QAction(this);
    mod_par->setText("Modify parameter");
    connect(mod_par, &QAction::triggered, this, &MainWindow::modify_parameter);
    ui->tableView_parameter->addAction(mod_par);

    QAction *rem_par = new QAction(this);
    rem_par->setText("Remove parameter");
    connect(rem_par, &QAction::triggered, this, &MainWindow::remove_parameter);
    ui->tableView_parameter->addAction(rem_par);

    QAction *refresh_par = new QAction(this);
    refresh_par->setText("Refresh list");
    connect(refresh_par, &QAction::triggered, this, &MainWindow::refresh_parameter);
    ui->tableView_parameter->addAction(refresh_par);
    //--Adminsitration actions
    QAction *refresh_ch_st = new QAction(this);
    refresh_ch_st->setText("Refresh list");
    connect(refresh_ch_st, &QAction::triggered, this, &MainWindow::refresh_ch_status);
    ui->tableView_ch_status->addAction(refresh_ch_st);

    QAction *set_ok_out_bt = new QAction(this);
    set_ok_out_bt->setText("Set batch to OK");
    connect(set_ok_out_bt, &QAction::triggered, this, &MainWindow::set_ok_in_bt);
    ui->tableView_in_bt->addAction(set_ok_out_bt);

    QAction *refresh_in_bt = new QAction(this);
    refresh_in_bt->setText("Refresh list");
    connect(refresh_in_bt, &QAction::triggered, this, &MainWindow::refresh_in_bt);
    ui->tableView_in_bt->addAction(refresh_in_bt);

    QAction *set_new_out_bt = new QAction(this);
    set_new_out_bt->setText("Set batch to NEW");
    connect(set_new_out_bt, &QAction::triggered, this, &MainWindow::set_new_out_bt);
    ui->tableView_out_bt->addAction(set_new_out_bt);

    QAction *refresh_out_bt = new QAction(this);
    refresh_out_bt->setText("Refresh list");
    connect(refresh_out_bt, &QAction::triggered, this, &MainWindow::refresh_out_bt);
    ui->tableView_out_bt->addAction(refresh_out_bt);

    QAction *get_node_info = new QAction(this);
    get_node_info->setText("Refresh Node info");
    connect(get_node_info, &QAction::triggered, this, &MainWindow::Get_node_ops);
    ui->label_node_info->addAction(get_node_info);

    QAction *table_reload_serv_act = new QAction(this);
    table_reload_serv_act->setText("Table reload request to client");
    connect(table_reload_serv_act, &QAction::triggered, this, &MainWindow::Table_reload_request_server);
    ui->label_node_info->addAction(table_reload_serv_act);

//    QAction *register_node_act = new QAction(this);
//    register_node_act->setText("Open registration for node");
//    connect(register_node_act, &QAction::triggered, this, &MainWindow::Register_node);
//    ui->label_node_info->addAction(register_node_act);

    QAction *start_sym_act = new QAction(this);
    start_sym_act->setText("Start service");
    connect(start_sym_act, &QAction::triggered, this, &MainWindow::Start_sym_service);
    ui->label_node_info->addAction(start_sym_act);

    QAction *stop_sym_act = new QAction(this);
    stop_sym_act->setText("Stop service");
    connect(stop_sym_act, &QAction::triggered, this, &MainWindow::Stop_sym_service);
    ui->label_node_info->addAction(stop_sym_act);

    QAction *sync_trigger_sym_act = new QAction(this);
    sync_trigger_sym_act->setText("Create sym triggers");
    connect(sync_trigger_sym_act, &QAction::triggered, this, &MainWindow::Sync_sym_triggers);
    ui->label_node_info->addAction(sync_trigger_sym_act);

    QAction *drop_trigger_sym_act = new QAction(this);
    drop_trigger_sym_act->setText("Drop sym triggers");
    connect(drop_trigger_sym_act, &QAction::triggered, this, &MainWindow::Sync_sym_triggers);
    ui->label_node_info->addAction(drop_trigger_sym_act);

    connect(ui->actionClose_project, &QAction::triggered, this, &MainWindow::Display_projects);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    QAction *set_host_info_child = new QAction(this);
    set_host_info_child->setText("Set connection info");
    connect(set_host_info_child, &QAction::triggered, this, &MainWindow::Set_child_host_info);
    ui->tableView_node_children->addAction(set_host_info_child);

    QAction *table_req_reload_client = new QAction(this);
    table_req_reload_client->setText("Table reload request to server");
    connect(table_req_reload_client, &QAction::triggered, this, &MainWindow::Table_reload_request_client);
    ui->tableView_node_children->addAction(table_req_reload_client);

    QAction *get_bt_err_child = new QAction(this);
    get_bt_err_child->setText("Get batch errors");
    connect(get_bt_err_child, &QAction::triggered, this, &MainWindow::Get_bt_error_child);
    ui->tableView_node_children->addAction(get_bt_err_child);

    QAction *child_set_new_out_bt = new QAction(this);
    child_set_new_out_bt->setText("Set batch to NEW");
    connect(child_set_new_out_bt, &QAction::triggered, this, &MainWindow::child_set_new_out_bt);
    ui->tableView_node_children_out_bt->addAction(child_set_new_out_bt);

    QAction *child_set_ok_in_bt = new QAction(this);
    child_set_ok_in_bt->setText("Set batch to OK");
    connect(child_set_ok_in_bt, &QAction::triggered, this, &MainWindow::child_set_ok_in_bt);
    ui->tableView_node_children_in_bt->addAction(child_set_ok_in_bt);

    QTimer::singleShot(300,this,SLOT(Display_administration()));
    QTimer::singleShot(300,this,SLOT(Display_projects()));
    //QTimer::singleShot(300,this,SLOT(Get_node_ops()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Full_screen()
{
    if(!this->isFullScreen()){
        ui->actionFull_screen->setText("Exit full screen");
        this->showFullScreen();
    }
    else{
        ui->actionFull_screen->setText("Full screen");
        this->showMaximized();
    }
}

void MainWindow::Display_configuration()
{
    this->setWindowTitle("Replicator - Configuration");
    ui->stackedWidget_dash->setCurrentIndex(0);
    ui->tabWidget_config->setCurrentIndex(0);
}

void MainWindow::Display_administration()
{
    this->setWindowTitle("Replicator - Administration");
    ui->stackedWidget_dash->setCurrentIndex(1);
    ui->tabWidget_admin->setCurrentIndex(0);
}

void MainWindow::Display_projects()
{
    ui->frame->setEnabled(false);
    Dialog_project_list dl;
    dl.exec();
    if(dl.is_exit | dl.selected_pro.isEmpty())close();
    ui->label_project_name->setText(dl.selected_pro);
    QSqlQuery qr(db);
    qr.prepare("select host,port,id from project where name='"+dl.selected_pro+"';");
    if(!qr.exec()){
        QMessageBox::information(this,"DB Error",qr.lastError().text());
        close();
    }
    while (qr.next()) {
        bool *ok;
       ui->lineEdit_host->setText(qr.value(0).toString());
       ui->spinBox_port->setValue(qr.value(1).toInt(ok));
       project_id = qr.value(2).toInt(ok);
       ui->frame->setEnabled(true);
    }
    ui->frame->setEnabled(true);
    master_dbms="";
    ui->label_node_info->setText("");
}

void MainWindow::Display_node_child_info()
{
    QSqlQuery qr(db);
    QStandardItemModel *mdl = new QStandardItemModel();
    QString query("select nodeid,externalid,registred,\"host\",port from nodes where project_id =");
    query.append(QVariant(project_id).toString()); query.append(" and is_master=0;");
    mdl->setColumnCount(5);
    QStringList labels;
    labels<<"nodeId"<<"externalId"<<"registered"<<"host"<<"port";
    if(!qr.exec(query)){
        QMessageBox::information(this,"Error",qr.lastError().text());
        return;
    }
    while (qr.next()) {
                        mdl->setRowCount(mdl->rowCount()+1);
                        mdl->setData(mdl->index(mdl->rowCount()-1,0,QModelIndex()),qr.value(0),Qt::EditRole);
                        mdl->setData(mdl->index(mdl->rowCount()-1,1,QModelIndex()),qr.value(1),Qt::EditRole);
                        mdl->setData(mdl->index(mdl->rowCount()-1,2,QModelIndex()),qr.value(2),Qt::EditRole);
                        mdl->setData(mdl->index(mdl->rowCount()-1,3,QModelIndex()),qr.value(3),Qt::EditRole);
                        mdl->setData(mdl->index(mdl->rowCount()-1,4,QModelIndex()),qr.value(4),Qt::EditRole);
    }
    mdl->setHorizontalHeaderLabels(labels);
    ui->tableView_node_children->setModel(mdl);
    ui->tableView_node_children->setColumnWidth(0,(ui->tableView_node_children->width()/5));
    ui->tableView_node_children->setColumnWidth(1,(ui->tableView_node_children->width()/5));
    ui->tableView_node_children->setColumnWidth(2,(ui->tableView_node_children->width()/5));
    ui->tableView_node_children->setColumnWidth(3,(ui->tableView_node_children->width()/5));
    ui->tableView_node_children->setColumnWidth(4,(ui->tableView_node_children->width()/5));
}

void MainWindow::Get_node_ops()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/node");
    req_op = "master_node_detail";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::Register_node()
{
    Dialog_open_registeration_node dl(this);
    dl.exec();
}

void MainWindow::Start_sym_service()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/start");

    req_op = "sym_service";
    req_manager->post(QNetworkRequest(QUrl(url)),QByteArray());
}
void MainWindow::Stop_sym_service()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/stop");
    req_op = "sym_service";
    req_manager->post(QNetworkRequest(QUrl(url)),QByteArray());
}

void MainWindow::Sync_sym_triggers()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/synctriggers");
    req_op = "Sync_sym_triggers";
    req_manager->post(QNetworkRequest(QUrl(url)),QByteArray());
}

void MainWindow::Drop_sym_triggers()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/droptriggers");
    req_op = "Drop_sym_triggers";
    req_manager->post(QNetworkRequest(QUrl(url)),QByteArray());
}

void MainWindow::Set_child_host_info()
{
    QItemSelectionModel *selectionmodel = ui->tableView_node_children->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    Dialog_node_child_info dl;
    QAbstractItemModel *mdl =  ui->tableView_node_children->model();
    dl.node_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.project_id = QVariant(project_id).toString();
    dl.exec();
    Display_node_child_info();
}

void MainWindow::Get_bt_error_child()
{
    //--Get host and port
    QSqlQuery qr(db);
            QItemSelectionModel *selectionmodel = ui->tableView_node_children->selectionModel();
            QModelIndexList indexes = selectionmodel->selectedIndexes();
            QModelIndex index;
            if (indexes.isEmpty())return;
            int row=0;
            foreach(index, indexes)row = index.row();
            QAbstractItemModel *mdl =  ui->tableView_node_children->model();
            QString node_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    qr.prepare("select host,port from nodes where project_id=:project_id and nodeid=:nodeid;");
    qr.bindValue(":project_id",project_id);
    qr.bindValue(":nodeid",node_id);
    if(!qr.exec()){
        QMessageBox::information(this,"DB Error",qr.lastError().text());
        return;
    }
    while (qr.next()) {
        child_host=qr.value(0).toString();
        child_port=qr.value(1).toString();
    }

    //--
    refresh_child_out_bt();
    refresh_child_in_bt();
    ui->groupBox_child_batch->setTitle("Batch errors for node_id : "+node_id);
}

void MainWindow::Table_reload_request_server()
{
    QSqlQuery qr(db);
    Dialog_table_reload_request dl;
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    qr.prepare("select nodeid from nodes where project_id=:project_id and is_master=1;");
    qr.bindValue(":project_id",project_id);
    if(!qr.exec()){
        QMessageBox::information(this,"Table_reload_request_server",qr.lastError().text());
        return;
    }
    while (qr.next()) {
        dl.source_node_id = qr.value(0).toString();
    }
    qr.prepare("select nodeid from nodes where project_id=:project_id and is_master=0;");
    qr.bindValue(":project_id",project_id);
    if(!qr.exec()){
        QMessageBox::information(this,"Table_reload_request_server",qr.lastError().text());
        return;
    }
    while (qr.next()) {
        dl.target_node_ids<< qr.value(0).toString();
    }
    if(!dl.source_node_id.isEmpty()) dl.exec();
}

void MainWindow::Table_reload_request_client()
{
    Dialog_table_reload_request dl;
    QSqlQuery qr(db);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    QItemSelectionModel *selectionmodel = ui->tableView_node_children->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_node_children->model();
    dl.source_node_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    qr.prepare("select nodeid from nodes where project_id=:project_id and is_master=1;");
    qr.bindValue(":project_id",project_id);
    if(!qr.exec()){
        QMessageBox::information(this,"Table_reload_request_client",qr.lastError().text());
        return;
    }
    while (qr.next()) {
        dl.target_node_ids<<  qr.value(0).toString();
    }
    if(!dl.source_node_id.isEmpty()) dl.exec();
}

void MainWindow::Get_out_metrics()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query="
                +"select (select count(batch_id) from sym_outgoing_batch where status = 'NE') as \"NEW\""
                +","
                +"(select count(batch_id) from sym_outgoing_batch where status = 'LD') as \"LOAD\""
                +","
                +"(select count(batch_id) from sym_outgoing_batch where status = 'OK') as \"OK\""
                +","
                +"(select database_type from sym_node where node_id = '"+master_nodeid+"') as \"DBMS\";"
                );
    out_metrics_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::channel_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Channel table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        lst_channel_id.clear();
        for(int i=0;i<mdl->rowCount();i++){
            lst_channel_id<<mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString();
        }
        ui->tableView_channel->setModel(mdl);
        ui->tableView_channel->resizeColumnsToContents();
        ui->tableView_channel->resizeRowsToContents();
}

void MainWindow::node_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Node table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        lst_node_id.clear();
        lst_external_id.clear();
        for(int i=0;i<mdl->rowCount();i++){
            lst_node_id<<mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString();
            lst_external_id<<mdl->index(i,2,QModelIndex()).data(Qt::EditRole).toString();
        }
        ui->tableView_node->setModel(mdl);
        ui->tableView_node->resizeColumnsToContents();
        ui->tableView_node->resizeRowsToContents();
}

void MainWindow::node_group_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Node group table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        lst_node_group.clear();
        for(int i=0;i<mdl->rowCount();i++){
            lst_node_group<<mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString();
        }
        ui->tableView_node_group->setModel(mdl);
        ui->tableView_node_group->resizeColumnsToContents();
        ui->tableView_node_group->resizeRowsToContents();
}

void MainWindow::node_group_link_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Node group link table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_node_group_link->setModel(mdl);
        ui->tableView_node_group_link->resizeColumnsToContents();
        ui->tableView_node_group_link->resizeRowsToContents();
}

void MainWindow::router_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Router table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        lst_router.clear();
        for(int i=0;i<mdl->rowCount();i++){
            lst_router<<mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString();
        }
        ui->tableView_router->setModel(mdl);
        ui->tableView_router->resizeColumnsToContents();
        ui->tableView_router->resizeRowsToContents();
}

void MainWindow::trigger_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Trigger table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        lst_trigger.clear();
        for(int i=0;i<mdl->rowCount();i++){
            lst_trigger<<mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString();
        }
        ui->tableView_trigger->setModel(mdl);
        ui->tableView_trigger->resizeColumnsToContents();
        ui->tableView_trigger->resizeRowsToContents();
}

void MainWindow::trigger_router_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Trigger router table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_trigger_router->setModel(mdl);
        ui->tableView_trigger_router->resizeColumnsToContents();
        ui->tableView_trigger_router->resizeRowsToContents();
}

void MainWindow::notification_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Notification table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_notification->setModel(mdl);
        ui->tableView_notification->resizeColumnsToContents();
        ui->tableView_notification->resizeRowsToContents();
}

void MainWindow::monitor_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Monitor table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_monitor->setModel(mdl);
        ui->tableView_monitor->resizeColumnsToContents();
        ui->tableView_monitor->resizeRowsToContents();
}

void MainWindow::parameter_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Parameter table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_parameter->setModel(mdl);
        ui->tableView_parameter->resizeColumnsToContents();
        ui->tableView_parameter->resizeRowsToContents();
}

void MainWindow::req_managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    QSqlQuery qr(db);
    if( !response.contains("executeQuery") && (response.contains("failed") | response.contains("error"))){
        QMessageBox::information(this,"Error",response);
        return;
    }
    if(req_op=="remove_channel"){
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/querynode?query=select%20*%20from%20sym_channel;");
        channel_manager->get(QNetworkRequest(QUrl(url)));
    }
    if(req_op=="remove_node_group"){
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/querynode?query=select%20*%20from%20sym_node_group;");
        node_group_manager->get(QNetworkRequest(QUrl(url)));
    }
    if(req_op=="remove_node_group_link"){
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/querynode?query=select%20*%20from%20sym_node_group_link;");
        node_group_link_manager->get(QNetworkRequest(QUrl(url)));
    }
    if(req_op=="remove_router"){
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/querynode?query=select%20*%20from%20sym_router;");
        router_manager->get(QNetworkRequest(QUrl(url)));
    }
    if(req_op=="remove_trigger"){
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/querynode?query=select%20*%20from%20sym_trigger;");
        trigger_manager->get(QNetworkRequest(QUrl(url)));
    }
    if(req_op=="remove_trigger_router"){
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/querynode?query=select%20*%20from%20sym_trigger_router;");
        trigger_router_manager->get(QNetworkRequest(QUrl(url)));
    }
    if(req_op=="remove_notification"){
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/querynode?query=select%20*%20from%20sym_notification;");
        notification_manager->get(QNetworkRequest(QUrl(url)));
    }
    if(req_op=="remove_monitor"){
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/querynode?query=select%20*%20from%20sym_monitor;");
        monitor_manager->get(QNetworkRequest(QUrl(url)));
    }
    if(req_op=="remove_parameter"){
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/querynode?query=select%20*%20from%20sym_parameter;");
        parameter_manager->get(QNetworkRequest(QUrl(url)));
    }
    if(req_op=="set_new_out_bt" ){
        refresh_out_bt();
    }
    if(req_op=="set_ok_in_bt"){
        refresh_in_bt();
    }
    if(req_op=="master_node_detail"){
        QString Master_node_info,nodeId,externalId;
        QXmlStreamReader reader(response);
        Master_node_info.append("<p><strong>Master Node details:</stong></p>");
        while(!reader.atEnd() && !reader.hasError()) {
            if(reader.readNext() == QXmlStreamReader::StartElement  ) {
                if(reader.name() =="nodeId") {
                    nodeId=reader.readElementText();
                    Master_node_info.append("<p>  nodeId : "+nodeId+"</p>");
                }
                if(reader.name() =="externalId"){
                    externalId=reader.readElementText();
                    Master_node_info.append("<p>  externalId : "+externalId+"</p>");
                }
                if(reader.name() =="registrationServer") Master_node_info.append("<p>  registrationServer : "+reader.readElementText()+"</p>");
            }
        }
        master_nodeid = nodeId;
        qr.prepare("select id from nodes where project_id = :project_id and is_master = 1;");
        qr.bindValue(":project_id",project_id);
        if(!qr.exec()){
            QMessageBox::information(this,"master_node_detail1",qr.lastError().text());
            return;
        }
        int master_id;
        bool *ok;
        bool exists=false;
        while (qr.next()) {
            master_id=qr.value(0).toInt(ok);
            exists=true;
        }
        if(!exists){
            qr.prepare("insert into nodes (project_id, externalid, nodeid, is_master) values (:project_id, :externalid, :nodeid, 1);");
            qr.bindValue(":project_id",project_id);
            qr.bindValue(":externalid",externalId);
            qr.bindValue(":nodeid",nodeId);
            //qDebug()<<"Details: "<<project_id<<" "<<externalId<<" "<<nodeId;
            if(!qr.exec()){
                QMessageBox::information(this,"master_node_detail2",qr.lastError().text()+"\n"+qr.lastQuery());
                return;
            }
        }
        else{
            qr.prepare("update nodes set externalid=:externalid, nodeid=:nodeid where project_id=:project_id and is_master = 1;");
            qr.bindValue(":project_id",project_id);
            qr.bindValue(":externalid",externalId);
            qr.bindValue(":nodeid",nodeId);
            if(!qr.exec()){
                QMessageBox::information(this,"master_node_detail",qr.lastError().text());
                return;
            }
        }
        ui->label_node_info->setText(Master_node_info);
        if(master_dbms!=""){
            ui->label_node_info->setText(
                        ui->label_node_info->text()
                        +"<p>DBMS: "
                        +master_dbms
                        +"</p>"
                        );
        }
        QString url("http://"
                    +ui->lineEdit_host->text()
                    +":"
                    +QVariant(ui->spinBox_port->value()).toString()
                    +"/api/engine/children");
        req_op = "children_node_detail";
        req_manager->get(QNetworkRequest(QUrl(url)));
        Display_node_child_info();
        Get_out_metrics();

    }
    if(req_op=="children_node_detail"){
        QXmlStreamReader reader(response);
        QStringList externalId,nodeId,registered,registrationServer;
        while(!reader.atEnd() && !reader.hasError()) {
            if(reader.readNext() == QXmlStreamReader::StartElement  ) {
                if(reader.name() =="externalId") externalId<<reader.readElementText();
                if(reader.name() =="nodeId") nodeId<<reader.readElementText();
                if(reader.name() =="registered") registered<<reader.readElementText();
                 if(reader.name() =="registrationServer") registrationServer<<reader.readElementText();
            }
        }
        if(!registrationServer.contains("true")){
            for(int i=0;i<externalId.count();i++){
                qr.prepare("select id from nodes where project_id = :project_id and nodeid =:nodeid and is_master = 0;");
                qr.bindValue(":project_id",project_id);
                qr.bindValue(":nodeid",nodeId.at(i));
                if(!qr.exec()){
                    QMessageBox::information(this,"children_node_detail",qr.lastError().text());
                    return;
                }
                int master_id;
                bool *ok;
                bool exists=false;
                while (qr.next()) {
                    master_id=qr.value(0).toInt(ok);
                    exists=true;
                }
                if(!exists){
                    qr.prepare("insert into nodes (project_id, externalid, nodeid, registred, is_master) values(:project_id, :externalid, :nodeid, :registred, 0);");
                    qr.bindValue(":project_id",project_id);
                    qr.bindValue(":externalid",externalId.at(i));
                    qr.bindValue(":nodeid",nodeId.at(i));
                    qr.bindValue(":registred",registered.at(i));
                    if(!qr.exec()){
                        QMessageBox::information(this,"children_node_detail",qr.lastError().text());
                        return;
                    }
                }
            }
            Display_node_child_info();
        }
    }
    if(req_op=="sym_service" | req_op=="Sync_sym_triggers" | req_op=="Drop_sym_triggers"){
        if(!response.isEmpty())
        QMessageBox::information(this,"SymmetricDS Service",response);
    }
    if(req_op=="child_set_new_out_bt" ){
        refresh_child_out_bt();
    }
    if(req_op=="child_set_ok_in_bt"){
        refresh_child_in_bt();
    }

}

void MainWindow::ch_status_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Channel status request",jsonError.errorString());
            return;
        }
        QJsonArray obj1 = flowerJson.array();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setColumnCount(8);
        mdl->setRowCount(obj1.count());
        QStringList labels;
        labels<<"channelId"<<"enabled"<<"outgoingError"<<"incomingError"
             <<"batchToSendCount"<<"batchInErrorCount"<<"ignoreEnabled"
            <<"suspendEnabled";
        for(int i=0; i<obj1.count(); i++){
            QJsonObject tmp = obj1.at(i).toObject();
            mdl->setData(mdl->index(i,0,QModelIndex()),QVariant(tmp["channelId"].toString()),Qt::EditRole) ;
            mdl->setData(mdl->index(i,1,QModelIndex()),QVariant(tmp["enabled"].toBool()),Qt::EditRole) ;
            mdl->setData(mdl->index(i,2,QModelIndex()),QVariant(tmp["outgoingError"].toBool()),Qt::EditRole) ;
            mdl->setData(mdl->index(i,3,QModelIndex()),QVariant(tmp["incomingError"].toBool()),Qt::EditRole) ;
            mdl->setData(mdl->index(i,4,QModelIndex()),QVariant(tmp["batchToSendCount"].toInt()),Qt::EditRole) ;
            mdl->setData(mdl->index(i,5,QModelIndex()),QVariant(tmp["batchInErrorCount"].toInt()),Qt::EditRole) ;
            mdl->setData(mdl->index(i,6,QModelIndex()),QVariant(tmp["ignoreEnabled"].toBool()),Qt::EditRole) ;
            mdl->setData(mdl->index(i,7,QModelIndex()),QVariant(tmp["suspendEnabled"].toBool()),Qt::EditRole) ;
        }
        mdl->setHorizontalHeaderLabels(labels);
                ui->tableView_ch_status->setModel(mdl);
                ui->tableView_ch_status->resizeColumnsToContents();
                ui->tableView_ch_status->resizeRowsToContents();
                ui->tableView_ch_status->sortByColumn(0);
//                for(int i=0;i<mdl->rowCount();i++){
//                    QString out_er = mdl->index(i,2,QModelIndex()).data(Qt::EditRole).toString();
//                    QString in_er = mdl->index(i,3,QModelIndex()).data(Qt::EditRole).toString();
//                    if( out_er=="true" ){
//                        ui->tableView_ch_status->setItemDelegateForColumn(2, new RedTableDelegate(ui->tableView_ch_status));
//                    }
//                    if( in_er=="true" ){
//                        ui->tableView_ch_status->setItemDelegateForColumn(3, new RedTableDelegate(ui->tableView_ch_status));
//                    }
//                }

}

void MainWindow::out_bt_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Outgoing batches errors table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_out_bt->setModel(mdl);
        ui->tableView_out_bt->resizeColumnsToContents();
        ui->tableView_out_bt->resizeRowsToContents();
}

void MainWindow::in_bt_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Incoming batches errors request",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_in_bt->setModel(mdl);
        ui->tableView_in_bt->resizeColumnsToContents();
        ui->tableView_in_bt->resizeRowsToContents();
}

void MainWindow::child_out_bt_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Outgoing batches errors table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_node_children_out_bt->setModel(mdl);
        ui->tableView_node_children_out_bt->resizeColumnsToContents();
        ui->tableView_node_children_out_bt->resizeRowsToContents();
}

void MainWindow::child_in_bt_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Outgoing batches errors table",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_node_children_in_bt->setModel(mdl);
        ui->tableView_node_children_in_bt->resizeColumnsToContents();
        ui->tableView_node_children_in_bt->resizeRowsToContents();
}

void MainWindow::query_db_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"DB Query request",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        ui->tableView_query_db->setModel(mdl);
        ui->tableView_query_db->resizeColumnsToContents();
        ui->tableView_query_db->resizeRowsToContents();
}

void MainWindow::out_metrics_managerFinished(QNetworkReply *reply)
{
    QJsonParseError jsonError;
    QString response(reply->readAll());
    if(response.contains("executeQuery")){
        return;
    }
    response.replace("\n"," ");
    response.replace("\t"," ");
        QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
        if (jsonError.error != QJsonParseError::NoError){
            QMessageBox::information(this,"Outgoing Metrics request",jsonError.errorString());
            return;
        }
        QJsonObject obj1 = flowerJson.object();
        int result_count = obj1["nbrResults"].toInt();
        QStandardItemModel *mdl = new QStandardItemModel();
        mdl->setRowCount(result_count);
        QJsonArray obj2 = obj1["results"].toArray();
        bool set_col=false;
        bool set_colnum=false;
        int row_count = obj2.count();
        for(int i=0;i<row_count;i++){
            QJsonObject tmp = obj2.at(i).toObject();
            QJsonArray ar1 = tmp["columnData"].toArray();
            int col_count = ar1.count();
            if(!set_colnum)mdl->setColumnCount(col_count);
            QStringList labels;
            for(int r=0;r<col_count;r++){
                QJsonObject tmp2 = ar1.at(r).toObject();
                labels<<tmp2["name"].toString();
                mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
            }
            if(!set_col){
                mdl->setHorizontalHeaderLabels(labels);
                set_col=true;
            }
        }
        if(mdl->rowCount()==1 ){
            //--test
            //qDebug()<<"DBMS : "<<mdl->index(0,3,QModelIndex()).data(Qt::EditRole).toString();
            //
            ui->label_new_batch->setText(mdl->index(0,0,QModelIndex()).data(Qt::EditRole).toString());
            ui->label_load_batch->setText(mdl->index(0,1,QModelIndex()).data(Qt::EditRole).toString());
            ui->label_ok_batch->setText(mdl->index(0,2,QModelIndex()).data(Qt::EditRole).toString());
            if(master_dbms=="" && ui->label_node_info->text()!=""){
                master_dbms = mdl->index(0,3,QModelIndex()).data(Qt::EditRole).toString();
                ui->label_node_info->setText(
                            ui->label_node_info->text()
                            +"<p>DBMS: "
                            +master_dbms
                            +"</p>"
                            );
            }
            QTimer::singleShot(2000,this,SLOT(Get_out_metrics()));
        }

}

void MainWindow::completer_managerFinished(QNetworkReply *reply)
{
        QJsonParseError jsonError;
        QString response(reply->readAll());
        if(response.contains("executeQuery")){
            return;
        }
        response.replace("\t","");
        response.replace("\n","");

            QJsonDocument flowerJson = QJsonDocument::fromJson(response.toUtf8(),&jsonError);
            if (jsonError.error != QJsonParseError::NoError){
                QMessageBox::information(this,"Completer lists",jsonError.errorString());
                return;
            }
            QJsonObject obj1 = flowerJson.object();
            int result_count = obj1["nbrResults"].toInt();
            QStandardItemModel *mdl = new QStandardItemModel();
            mdl->setRowCount(result_count);
            QJsonArray obj2 = obj1["results"].toArray();
            bool set_col=false;
            bool set_colnum=false;
            int row_count = obj2.count();
            for(int i=0;i<row_count;i++){
                QJsonObject tmp = obj2.at(i).toObject();
                QJsonArray ar1 = tmp["columnData"].toArray();
                int col_count = ar1.count();
                if(!set_colnum)mdl->setColumnCount(col_count);
                QStringList labels;
                for(int r=0;r<col_count;r++){
                    QJsonObject tmp2 = ar1.at(r).toObject();
                    labels<<tmp2["name"].toString();
                    mdl->setData(mdl->index(i,r,QModelIndex()),QVariant(tmp2["value"].toString()),Qt::EditRole) ;
                }
                if(!set_col){
                    mdl->setHorizontalHeaderLabels(labels);
                    set_col=true;
                }
            }
            lst_table.clear();
            for(int i=0;i<mdl->rowCount();i++){
                lst_table<<mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString();
            }


}

void MainWindow::on_pushButton_connect_clicked()
{
    //--Configuration tables
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_channel;");
    channel_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node;";
    node_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node_group;";
    node_group_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node_group_link;";
    node_group_link_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_router;";
    router_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_trigger;";
    trigger_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_trigger_router;";
    trigger_router_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_monitor;";
    monitor_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_notification;";
    notification_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_parameter;";
    parameter_manager->get(QNetworkRequest(QUrl(url)));
    //--Administration tables
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/channelstatus";
    ch_status_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select * from sym_outgoing_batch where status = 'ER';";
    out_bt_manager->get(QNetworkRequest(QUrl(url)));
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select * from sym_incoming_batch where status = 'ER';";
    in_bt_manager->get(QNetworkRequest(QUrl(url)));
    //--Get tables
    url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=SELECT table_name FROM information_schema.tables WHERE table_schema='public' and table_name not like 'sym_%';";

    completer_manager->get(QNetworkRequest(QUrl(url)));
    Get_node_ops();

    if(!ui->pushButton_connect->isChecked()){
        ui->pushButton_connect->setChecked(true);
        ui->pushButton_connect->setText("Disconnect");
        ui->lineEdit_host->setEnabled(false);
    }
    else{
        ui->pushButton_connect->setChecked(false);
        ui->pushButton_connect->setText("Connect");
        ui->lineEdit_host->setEnabled(true);
    }
}

void MainWindow::on_lineEdit_chennel_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_channel->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_channel->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_channel->hideRow(i);
        }
    }
}

void MainWindow::on_lineEdit_node_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_node->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_node->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_node->hideRow(i);
        }
    }
}

void MainWindow::on_lineEdit_node_group_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_node_group->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_node_group->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_node_group->hideRow(i);
        }
    }
}

void MainWindow::on_lineEdit_node_group_link_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_node_group_link->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_node_group_link->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_node_group_link->hideRow(i);
        }
    }
}

void MainWindow::on_lineEdit_router_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_router->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_router->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_router->hideRow(i);
        }
    }
}

void MainWindow::on_lineEdit_trigger_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_trigger->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_trigger->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_trigger->hideRow(i);
        }
    }
}

void MainWindow::on_lineEdit_trigger_route_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_trigger_router->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_trigger_router->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_trigger_router->hideRow(i);
        }
    }
}

void MainWindow::add_channel()
{
    Dialog_channel dl(this);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_channel;");
    channel_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::modify_channel()
{
    QItemSelectionModel *selectionmodel = ui->tableView_channel->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_channel->model();
    Dialog_channel dl(this);
    for(int i=0;i<mdl->columnCount();i++){
        dl.data<<mdl->index(row,i,QModelIndex()).data(Qt::EditRole).toString();
    }
    dl.channel_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_channel;");
    channel_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::remove_channel()
{
    QMessageBox msgBox;
      msgBox.setText("This channel will be removed.");
      msgBox.setInformativeText("Are you sure to delete this channel?");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              break;
          case QMessageBox::Cancel:
              return;
          default:
              return;
        }
    QItemSelectionModel *selectionmodel = ui->tableView_channel->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_channel->model();
    QString channel_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=delete from sym_channel where channel_id = '"+channel_id.replace("'","''")+"';");
    req_op = "remove_channel";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_channel()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_channel;");
    channel_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_node()
{
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node;";
    node_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::add_node_group()
{
    Dialog_node_group dl(this);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node_group;";
    node_group_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::modify_node_group()
{
    QItemSelectionModel *selectionmodel = ui->tableView_node_group->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_node_group->model();
    Dialog_node_group dl(this);
    for(int i=0;i<mdl->columnCount();i++){
        dl.data<<mdl->index(row,i,QModelIndex()).data(Qt::EditRole).toString();
    }
    dl.node_group_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node_group;";
    node_group_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::remove_node_group()
{
    QMessageBox msgBox;
      msgBox.setText("This node_group will be removed.");
      msgBox.setInformativeText("Are you sure to delete this node_group?");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              break;
          case QMessageBox::Cancel:
              return;
          default:
              return;
        }
    QItemSelectionModel *selectionmodel = ui->tableView_node_group->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_node_group->model();
    QString node_group_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=delete from sym_node_group where node_group_id = '"+node_group_id.replace("'","''")+"';");
    req_op = "remove_node_group";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_node_group()
{
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node_group;";
    node_group_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::add_node_group_link()
{
    Dialog_node_group_link dl(this);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.lst_node_group = lst_node_group;
    dl.exec();
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node_group_link;";
    node_group_link_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::modify_node_group_link()
{
    QItemSelectionModel *selectionmodel = ui->tableView_node_group_link->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_node_group_link->model();
    Dialog_node_group_link dl(this);
    for(int i=0;i<mdl->columnCount();i++){
        dl.data<<mdl->index(row,i,QModelIndex()).data(Qt::EditRole).toString();
    }
    dl.source_node_group_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.target_node_group_id = mdl->index(row,1,QModelIndex()).data(Qt::EditRole).toString();
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node_group_link;";
    node_group_link_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::remove_node_group_link()
{
    QMessageBox msgBox;
      msgBox.setText("This node_group_link will be removed.");
      msgBox.setInformativeText("Are you sure to delete this node_group_link?");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              break;
          case QMessageBox::Cancel:
              return;
          default:
              return;
        }
    QItemSelectionModel *selectionmodel = ui->tableView_node_group_link->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_node_group_link->model();
    QString source_node_group_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString target_node_group_id = mdl->index(row,1,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=delete from sym_node_group_link where source_node_group_id = '"+source_node_group_id.replace("'","''")+"' and target_node_group_id = '"+target_node_group_id.replace("'","''")+"';");
    req_op = "remove_node_group_link";
    req_manager->get(QNetworkRequest(QUrl(url)));

}

void MainWindow::refresh_node_group_link()
{
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_node_group_link;";
    node_group_link_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::add_router()
{
    Dialog_router dl(this);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_router;");
    router_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::modify_router()
{
    QItemSelectionModel *selectionmodel = ui->tableView_router->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_router->model();
    Dialog_router dl(this);
    for(int i=0;i<mdl->columnCount();i++){
        dl.data<<mdl->index(row,i,QModelIndex()).data(Qt::EditRole).toString();
    }
    dl.router_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_router;");
    router_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::remove_router()
{
    QMessageBox msgBox;
      msgBox.setText("This router will be removed.");
      msgBox.setInformativeText("Are you sure to delete this router?");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              break;
          case QMessageBox::Cancel:
              return;
          default:
              return;
        }
    QItemSelectionModel *selectionmodel = ui->tableView_router->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_router->model();
    QString router_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=delete from sym_router where router_id = '"+router_id.replace("'","''")+"';");
    req_op = "remove_router";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_router()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_router;");
    router_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::add_trigger_router()
{
    Dialog_trigger_router dl(this);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.lst_trigger_id = lst_trigger;
    dl.lst_router_id = lst_router;
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_trigger_router;");
    trigger_router_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::modify_trigger_router()
{
    QItemSelectionModel *selectionmodel = ui->tableView_trigger_router->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_trigger_router->model();
    Dialog_trigger_router dl(this);
    for(int i=0;i<mdl->columnCount();i++){
        dl.data<<mdl->index(row,i,QModelIndex()).data(Qt::EditRole).toString();
    }
    dl.trigger_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.router_id = mdl->index(row,1,QModelIndex()).data(Qt::EditRole).toString();
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_trigger_router;");
    trigger_router_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::remove_trigger_router()
{
    QMessageBox msgBox;
      msgBox.setText("This trigger_router will be removed.");
      msgBox.setInformativeText("Are you sure to delete this trigger_router?");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              break;
          case QMessageBox::Cancel:
              return;
          default:
              return;
        }
    QItemSelectionModel *selectionmodel = ui->tableView_trigger_router->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_trigger_router->model();
    QString trigger_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString router_id = mdl->index(row,1,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=delete from sym_trigger_router where trigger_id = '"+trigger_id.replace("'","''")+"' and router_id = '"+router_id.replace("'","''")+"';");
    req_op = "remove_trigger_router";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_trigger_router()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_trigger_router;");
    trigger_router_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::add_monitor()
{
    Dialog_monitor dl(this);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_monitor;";
    monitor_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::modify_monitor()
{
    QItemSelectionModel *selectionmodel = ui->tableView_monitor->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_monitor->model();
    Dialog_monitor dl(this);
    for(int i=0;i<mdl->columnCount();i++){
        dl.data<<mdl->index(row,i,QModelIndex()).data(Qt::EditRole).toString();
    }
    dl.monitor_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_monitor;";
    monitor_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::remove_monitor()
{
    QMessageBox msgBox;
      msgBox.setText("This monitor will be removed.");
      msgBox.setInformativeText("Are you sure to delete this monitor?");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              break;
          case QMessageBox::Cancel:
              return;
          default:
              return;
        }
    QItemSelectionModel *selectionmodel = ui->tableView_monitor->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_monitor->model();
    QString monitor_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=delete from sym_monitor where monitor_id = '"+monitor_id.replace("'","''")+"';");
    req_op = "remove_monitor";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_monitor()
{
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_monitor;";
    monitor_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::add_parameter()
{
    Dialog_parameter dl(this);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.lst_external_id = lst_external_id;
    dl.lst_node_group = lst_node_group;
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_parameter;");
    parameter_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::modify_parameter()
{
    QItemSelectionModel *selectionmodel = ui->tableView_parameter->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_parameter->model();
    Dialog_parameter dl(this);
    for(int i=0;i<mdl->columnCount();i++){
        dl.data<<mdl->index(row,i,QModelIndex()).data(Qt::EditRole).toString();
    }
    dl.external_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.node_group_id = mdl->index(row,1,QModelIndex()).data(Qt::EditRole).toString();
    dl.param_key = mdl->index(row,2,QModelIndex()).data(Qt::EditRole).toString();
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_parameter;";
    parameter_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::remove_parameter()
{
    QMessageBox msgBox;
      msgBox.setText("This parameter will be removed.");
      msgBox.setInformativeText("Are you sure to delete this parameter?");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              break;
          case QMessageBox::Cancel:
              return;
          default:
              return;
        }
    QItemSelectionModel *selectionmodel = ui->tableView_parameter->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_parameter->model();
    QString external_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString node_group_id = mdl->index(row,1,QModelIndex()).data(Qt::EditRole).toString();
    QString param_key = mdl->index(row,2,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=delete from sym_parameter where external_id = '"+external_id.replace("'","''")+"' and node_group_id = '"+node_group_id.replace("'","''")+"' and param_key = '"+param_key+"';");
    req_op = "remove_parameter";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_parameter()
{
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select%20*%20from%20sym_parameter;";
    parameter_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_ch_status()
{
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/channelstatus";
    ch_status_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_in_bt()
{
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select * from sym_incoming_batch where status = 'ER';";
    in_bt_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::set_new_out_bt()
{
    QItemSelectionModel *selectionmodel = ui->tableView_out_bt->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_out_bt->model();
    QString batch_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=update sym_outgoing_batch set status = 'NE', error_flag = 0 where batch_id = '"+batch_id+"';");
    req_op = "set_new_out_bt";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::set_ok_in_bt()
{
    QItemSelectionModel *selectionmodel = ui->tableView_in_bt->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_in_bt->model();
    QString batch_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=update sym_incoming_batch set status = 'OK', error_flag = 0 where batch_id = '"+batch_id+"';");
    req_op = "set_ok_in_bt";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_out_bt()
{
    QString url = "http://"
            +ui->lineEdit_host->text()
            +":"
            +QVariant(ui->spinBox_port->value()).toString()
            +"/api/engine/querynode?query=select * from sym_outgoing_batch where status = 'ER';";
    out_bt_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::child_set_new_out_bt()
{
    QItemSelectionModel *selectionmodel = ui->tableView_node_children_out_bt->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_node_children_out_bt->model();
    QString batch_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +child_host
                +":"
                +child_port
                +"/api/engine/querynode?query=update sym_outgoing_batch set status = 'NE', error_flag = 0 where batch_id = '"+batch_id+"';");
    req_op = "child_set_new_out_bt";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::child_set_ok_in_bt()
{
    QItemSelectionModel *selectionmodel = ui->tableView_node_children_in_bt->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_node_children_in_bt->model();
    QString batch_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +child_host
                +":"
                +child_port
                +"/api/engine/querynode?query=update sym_incoming_batch set status = 'OK', error_flag = 0 where batch_id = '"+batch_id+"';");
    req_op = "child_set_ok_in_bt";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_child_out_bt()
{
    QString url = "http://"
            +child_host
            +":"
            +child_port
            +"/api/engine/querynode?query=select * from sym_outgoing_batch where status = 'ER';";
    child_out_bt_manager->get(QNetworkRequest(QUrl(url)));

}

void MainWindow::refresh_child_in_bt()
{
    QString url = "http://"
            +child_host
            +":"
            +child_port
            +"/api/engine/querynode?query=select * from sym_incoming_batch where status = 'ER';";
    child_in_bt_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::add_notification()
{
    Dialog_notification dl(this);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_notification;");
    notification_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::modify_notification()
{
    QItemSelectionModel *selectionmodel = ui->tableView_notification->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_notification->model();
    Dialog_notification dl(this);
    for(int i=0;i<mdl->columnCount();i++){
        dl.data<<mdl->index(row,i,QModelIndex()).data(Qt::EditRole).toString();
    }
    dl.notification_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_notification;");
    notification_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::remove_notification()
{
    QMessageBox msgBox;
      msgBox.setText("This notification will be removed.");
      msgBox.setInformativeText("Are you sure to delete this notification?");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              break;
          case QMessageBox::Cancel:
              return;
          default:
              return;
        }
    QItemSelectionModel *selectionmodel = ui->tableView_notification->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_notification->model();
    QString notification_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=delete from sym_notification where notification_id = '"+notification_id.replace("'","''")+"';");
    req_op = "remove_notification";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_notification()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_notification;");
    notification_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::add_trigger()
{
    Dialog_trigger dl(this);
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.lst_table = lst_table;
    dl.lst_channel_id = lst_channel_id;
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_trigger;");
    trigger_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::modify_trigger()
{
    QItemSelectionModel *selectionmodel = ui->tableView_trigger->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_trigger->model();
    Dialog_trigger dl(this);
    for(int i=0;i<mdl->columnCount();i++){
        dl.data<<mdl->index(row,i,QModelIndex()).data(Qt::EditRole).toString();
    }
    dl.trigger_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    dl.host = ui->lineEdit_host->text();
    dl.port = QVariant(ui->spinBox_port->value()).toString();
    dl.exec();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_trigger;");
    trigger_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::remove_trigger()
{
    QMessageBox msgBox;
      msgBox.setText("This trigger will be removed.");
      msgBox.setInformativeText("Are you sure to delete this trigger?");
      msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Cancel);
      int ret = msgBox.exec();
      switch (ret) {
          case QMessageBox::Ok:
              break;
          case QMessageBox::Cancel:
              return;
          default:
              return;
        }
    QItemSelectionModel *selectionmodel = ui->tableView_trigger->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView_trigger->model();
    QString trigger_id = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=delete from sym_trigger where trigger_id = '"+trigger_id.replace("'","''")+"';");
    req_op = "remove_trigger";
    req_manager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::refresh_trigger()
{
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query=select%20*%20from%20sym_trigger;");
    trigger_manager->get(QNetworkRequest(QUrl(url)));
}


void MainWindow::on_lineEdit_notification_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_notification->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_notification->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_notification->hideRow(i);
        }
    }
}

void MainWindow::on_lineEdit_monitor_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_monitor->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_monitor->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_monitor->hideRow(i);
        }
    }
}

void MainWindow::on_lineEdit_parameter_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_parameter->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_parameter->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_parameter->hideRow(i);
        }
    }
}

void MainWindow::on_lineEdit_ch_status_filter_textChanged(const QString &arg1)
{
    QAbstractItemModel *mdl = ui->tableView_ch_status->model();
    int row_count =mdl->rowCount();
    for(int i=0;i<row_count;i++){
        ui->tableView_ch_status->showRow(i);
        if(!mdl->index(i,0,QModelIndex()).data(Qt::EditRole).toString().contains(arg1)){
            ui->tableView_ch_status->hideRow(i);
        }
    }
}

void MainWindow::on_pushButton_query_db_clicked()
{
    if(ui->plainTextEdit_query_db->document()->toPlainText().isEmpty())return;
    QString url("http://"
                +ui->lineEdit_host->text()
                +":"
                +QVariant(ui->spinBox_port->value()).toString()
                +"/api/engine/querynode?query="+ui->plainTextEdit_query_db->document()->toPlainText());
    query_db_manager->get(QNetworkRequest(QUrl(url.replace("+","%2B"))));
}

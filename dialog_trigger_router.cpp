#include "dialog_trigger_router.h"
#include "ui_dialog_trigger_router.h"
#include <QCompleter>

Dialog_trigger_router::Dialog_trigger_router(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_trigger_router)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));
}

Dialog_trigger_router::~Dialog_trigger_router()
{
    delete ui;
}

void Dialog_trigger_router::initialisation()
{
    QCompleter *cpl_tr = new QCompleter(lst_trigger_id,this);
    ui->lineEdit_trigger_id->setCompleter(cpl_tr);
    QCompleter *cpl_rt = new QCompleter(lst_router_id,this);
    ui->lineEdit_trigger_id->setCompleter(cpl_rt);
    bool *ok;
    if(data.count()>0){
        ui->lineEdit_trigger_id->setText(data.at(0));
        ui->lineEdit_router_id->setText(data.at(1));
        ui->spinBox_enabled->setValue(QVariant(data.at(2)).toInt(ok));
        ui->spinBox_initial_load_order->setValue(QVariant(data.at(3)).toInt(ok));
        ui->lineEdit_initial_load_select->setText(data.at(4));
        ui->lineEdit_initial_load_delete_stmt->setText(data.at(5));
        ui->spinBox_ping_back_enabled->setValue(QVariant(data.at(6)).toInt(ok));
        ui->lineEdit_description->setText(data.at(10));
    }
}

void Dialog_trigger_router::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("executeQuery"))close();
    else if(response.contains("failed") | response.contains("error"))
        QMessageBox::information(this,"Error",response);
    else close();
}

void Dialog_trigger_router::on_pushButton_clicked()
{
    if(data.count()==0){
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=INSERT INTO sym_trigger_router "
                    +"(trigger_id, router_id, enabled, initial_load_order,"
                    +" initial_load_select, initial_load_delete_stmt, ping_back_enabled, "
                    +"create_time, last_update_by, last_update_time, description) "
                    +"VALUES('"
                +ui->lineEdit_trigger_id->text().replace("'","''")
                +"', '"
                +ui->lineEdit_router_id->text().replace("'","''")
                +"', "
                +QVariant(ui->spinBox_enabled->value()).toString().replace("'","''")
                +", "
                +QVariant(ui->spinBox_initial_load_order->value()).toString().replace("'","''")
                +", '"
                +ui->lineEdit_initial_load_select->text().replace("'","''")
                +"', '"
                +ui->lineEdit_initial_load_delete_stmt->text().replace("'","''")
                +"', "
                +QVariant(ui->spinBox_ping_back_enabled->value()).toString().replace("'","''")
                +", current_timestamp, 'admin', current_timestamp, '"
                +ui->lineEdit_description->text().replace("'","''")
                    +"');";
        manager->get(QNetworkRequest(QUrl(url)));
    }
    else{
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=UPDATE sym_trigger_router set trigger_id='"
                +ui->lineEdit_trigger_id->text().replace("'","''")
                +"', router_id='"
                +ui->lineEdit_router_id->text().replace("'","''")
                +"', enabled="
                +QVariant(ui->spinBox_enabled->value()).toString().replace("'","''")
                +", initial_load_order="
                +QVariant(ui->spinBox_initial_load_order->value()).toString().replace("'","''")
                +", initial_load_select='"
                +ui->lineEdit_initial_load_select->text().replace("'","''")
                +"', initial_load_delete_stmt='"
                +ui->lineEdit_initial_load_delete_stmt->text().replace("'","''")
                +"', ping_back_enabled="
                +QVariant(ui->spinBox_ping_back_enabled->value()).toString().replace("'","''")
                +", description='"
                +ui->lineEdit_description->text().replace("'","''")
                    +"' where router_id = '"+router_id.replace("'","''")+"'  and trigger_id = '"+trigger_id.replace("'","''")+"';";
        manager->get(QNetworkRequest(QUrl(url)));
    }
}

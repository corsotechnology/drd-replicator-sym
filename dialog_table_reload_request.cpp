#include "dialog_table_reload_request.h"
#include "ui_dialog_table_reload_request.h"

Dialog_table_reload_request::Dialog_table_reload_request(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_table_reload_request)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));
}

Dialog_table_reload_request::~Dialog_table_reload_request()
{
    delete ui;
}

void Dialog_table_reload_request::on_pushButton_clicked()
{
    if(ui->lineEdit_router_id->text().isEmpty() | ui->lineEdit_source_table_name->text().isEmpty())return;
    QString url("http://"
                +host
                +":"
                +port
                +"/api/engine/querynode?query=insert into SYM_TABLE_RELOAD_REQUEST (target_node_id, source_node_id, trigger_id, router_id, create_time, last_update_time) "
                +"values ('"+ui->comboBox_target_node_id->currentText().replace("'","''")
                +"', '"+ui->lineEdit_source_node_id->text().replace("'","''")
                +"', '"+ui->lineEdit_source_table_name->text().replace("'","''")
                +"', '"+ui->lineEdit_router_id->text().replace("'","''")+"', current_timestamp, current_timestamp) returning target_node_id;");
    manager->get(QNetworkRequest(QUrl(url.replace("+","%2B"))));
}

void Dialog_table_reload_request::initialisation()
{
    ui->lineEdit_source_node_id->setText(source_node_id);
    ui->comboBox_target_node_id->addItems(target_node_ids);
}

void Dialog_table_reload_request::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("failed") | response.contains("error")){
        QMessageBox::information(this,"Error",response);
        return;
    }
    else {
        QMessageBox::information(this,"Info","Request succeful.");
        close();
    }
}

#include "dialog_router.h"
#include "ui_dialog_router.h"

Dialog_router::Dialog_router(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_router)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));

}

Dialog_router::~Dialog_router()
{
    delete ui;
}

void Dialog_router::initialisation()
{
    bool *ok;
    if(data.count()>0){
        ui->lineEdit_router_id->setText(data.at(0));
        ui->lineEdit_target_catalog_name->setText(data.at(1));
        ui->lineEdit_target_schema_name->setText(data.at(2));
        ui->lineEdit_target_table_name->setText(data.at(3));
        ui->lineEdit_source_node_group_id->setText(data.at(4));
        ui->lineEdit_target_node_group_id->setText(data.at(5));
        ui->comboBox_router_type->setCurrentText(data.at(6));
        ui->plainTextEdit_router_expression->setPlainText(data.at(7));
        ui->spinBox_sync_on_update->setValue(QVariant(data.at(8)).toInt(ok));
        ui->spinBox_sync_on_insert->setValue(QVariant(data.at(9)).toInt(ok));
        ui->spinBox_sync_on_delete->setValue(QVariant(data.at(10)).toInt(ok));
        ui->spinBox_use_source_catalog_schema->setValue(QVariant(data.at(11)).toInt(ok));
        ui->lineEdit_description->setText(data.at(15));
    }
}

void Dialog_router::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("executeQuery") | response.contains("No results"))close();
    else if(response.contains("failed") | response.contains("error"))
        QMessageBox::information(this,"Error",response);
    else close();
}

void Dialog_router::on_pushButton_clicked()
{
    if(data.count()==0){
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=INSERT INTO sym_router (router_id, target_catalog_name, target_schema_name,"
                    +"target_table_name, source_node_group_id, target_node_group_id, router_type, "
                    +"router_expression, sync_on_update, sync_on_insert, sync_on_delete, use_source_catalog_schema, description, create_time, last_update_time) "
                    +"VALUES('"
                    +ui->lineEdit_router_id->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_target_catalog_name->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_target_schema_name->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_target_table_name->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_source_node_group_id->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_target_node_group_id->text().replace("'","''")
                    +"', '"
                    +ui->comboBox_router_type->currentText().replace("'","''")
                    +"', '"
                    +ui->plainTextEdit_router_expression->document()->toPlainText().replace("'","''")
                    +"', "
                    +QVariant(ui->spinBox_sync_on_update->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_sync_on_insert->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_sync_on_delete->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_use_source_catalog_schema->value()).toString().replace("'","''")
                    +", '"
                    +ui->lineEdit_description->text().replace("'","''")
                    +"', current_timestamp, current_timestamp);";
        manager->get(QNetworkRequest(QUrl(url)));
    }
    else{
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=UPDATE sym_router set router_id='"
                +ui->lineEdit_router_id->text().replace("'","''")
                +"', target_catalog_name='"
                +ui->lineEdit_target_catalog_name->text().replace("'","''")
                +"', target_schema_name='"
                +ui->lineEdit_target_schema_name->text().replace("'","''")
                +"', target_table_name='"
                +ui->lineEdit_target_table_name->text().replace("'","''")
                +"', source_node_group_id='"
                +ui->lineEdit_source_node_group_id->text().replace("'","''")
                +"', target_node_group_id='"
                +ui->lineEdit_target_node_group_id->text().replace("'","''")
                +"', router_type='"
                +ui->comboBox_router_type->currentText().replace("'","''")
                +"', router_expression='"
                +ui->plainTextEdit_router_expression->document()->toPlainText().replace("'","''")
                +"', sync_on_update="
                +QVariant(ui->spinBox_sync_on_update->value()).toString().replace("'","''")
                +", sync_on_insert="
                +QVariant(ui->spinBox_sync_on_insert->value()).toString().replace("'","''")
                +", sync_on_delete="
                +QVariant(ui->spinBox_sync_on_delete->value()).toString().replace("'","''")
                +", use_source_catalog_schema="
                +QVariant(ui->spinBox_use_source_catalog_schema->value()).toString().replace("'","''")
                +", description='"
                +ui->lineEdit_description->text().replace("'","''")
                    +"',last_update_time = current_timestamp where router_id = '"+router_id.replace("'","''")+"';";
        manager->get(QNetworkRequest(QUrl(url)));
    }
}

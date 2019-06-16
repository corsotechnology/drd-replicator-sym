#include "dialog_channel.h"
#include "ui_dialog_channel.h"


Dialog_channel::Dialog_channel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_channel)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));
}

Dialog_channel::~Dialog_channel()
{
    delete ui;
}

void Dialog_channel::initialisation()
{
    bool *ok;
    if(data.count()>0){
        ui->lineEdit_channel_id->setText(data.at(0));
        ui->spinBox_processing_order->setValue(QVariant(data.at(1)).toInt(ok));
        ui->spinBox_max_batch_size->setValue(QVariant(data.at(2)).toInt(ok));
        ui->spinBox_max_batch_to_send->setValue(QVariant(data.at(3)).toInt(ok));
        ui->spinBox_max_data_to_route->setValue(QVariant(data.at(4)).toInt(ok));
        ui->spinBox_extract_period_millis->setValue(QVariant(data.at(5)).toInt(ok));
        ui->spinBox_enabled->setValue(QVariant(data.at(6)).toInt(ok));
        ui->spinBox_use_old_data_to_route->setValue(QVariant(data.at(7)).toInt(ok));
        ui->spinBox_use_row_data_to_route->setValue(QVariant(data.at(8)).toInt(ok));
        ui->spinBox_use_pk_data_to_route->setValue(QVariant(data.at(9)).toInt(ok));
        ui->spinBox_reload_flag->setValue(QVariant(data.at(10)).toInt(ok));
        ui->spinBox_file_sync_flag->setValue(QVariant(data.at(11)).toInt(ok));
        ui->spinBox_contains_big_lob->setValue(QVariant(data.at(12)).toInt(ok));
        ui->comboBox_batch_algorithm->setCurrentText(data.at(13));
        ui->comboBox_data_loader_type->setCurrentText(data.at(14));
        ui->lineEdit_description->setText(data.at(15));
        ui->lineEdit_queue->setText(data.at(16));
        ui->spinBox_max_network_kbps->setValue(QVariant(data.at(17)).toInt(ok));

    }
}

void Dialog_channel::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("executeQuery"))close();
    else if(response.contains("failed") | response.contains("error"))
        QMessageBox::information(this,"Error",response);
    else close();
}

void Dialog_channel::on_pushButton_clicked()
{
    if(data.count()==0){
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=INSERT INTO sym_channel "
                    +"(channel_id, processing_order, max_batch_size, max_batch_to_send, max_data_to_route,"
                    +"extract_period_millis, enabled, use_old_data_to_route, use_row_data_to_route,"
                    +"use_pk_data_to_route, reload_flag, file_sync_flag, contains_big_lob, batch_algorithm,"
                    +" data_loader_type, description, queue, max_network_kbps) "
                    +"VALUES('"
                    +ui->lineEdit_channel_id->text().replace("'","''")
                    +"', "
                    +QVariant(ui->spinBox_processing_order->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_max_batch_size->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_max_batch_to_send->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_max_data_to_route->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_extract_period_millis->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_enabled->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_use_old_data_to_route->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_use_row_data_to_route->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_use_pk_data_to_route->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_reload_flag->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_file_sync_flag->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_contains_big_lob->value()).toString().replace("'","''")
                    +", '"
                    +ui->comboBox_batch_algorithm->currentText().replace("'","''")
                    +"', '"
                    +ui->comboBox_data_loader_type->currentText().replace("'","''")
                    +"', '"
                    +ui->lineEdit_description->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_queue->text().replace("'","''")
                    +"', "
                    +QVariant(ui->spinBox_max_network_kbps->value()).toString().replace("'","''")
                    +");";
        manager->get(QNetworkRequest(QUrl(url)));
    }
    else{
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=UPDATE sym_channel set channel_id='"
                    +ui->lineEdit_channel_id->text()
                    +"', processing_order="
                    +QVariant(ui->spinBox_processing_order->value()).toString().replace("'","''")
                    +", max_batch_size="
                    +QVariant(ui->spinBox_max_batch_size->value()).toString().replace("'","''")
                    +", max_batch_to_send="
                    +QVariant(ui->spinBox_max_batch_to_send->value()).toString().replace("'","''")
                    +", max_data_to_route="
                    +QVariant(ui->spinBox_max_data_to_route->value()).toString().replace("'","''")
                    +", extract_period_millis="
                    +QVariant(ui->spinBox_extract_period_millis->value()).toString().replace("'","''")
                    +", enabled="
                    +QVariant(ui->spinBox_enabled->value()).toString().replace("'","''")
                    +", use_old_data_to_route="
                    +QVariant(ui->spinBox_use_old_data_to_route->value()).toString().replace("'","''")
                    +", use_row_data_to_route="
                    +QVariant(ui->spinBox_use_row_data_to_route->value()).toString().replace("'","''")
                    +", use_pk_data_to_route="
                    +QVariant(ui->spinBox_use_pk_data_to_route->value()).toString().replace("'","''")
                    +", reload_flag="
                    +QVariant(ui->spinBox_reload_flag->value()).toString().replace("'","''")
                    +", file_sync_flag="
                    +QVariant(ui->spinBox_file_sync_flag->value()).toString().replace("'","''")
                    +", contains_big_lob="
                    +QVariant(ui->spinBox_contains_big_lob->value()).toString().replace("'","''")
                    +", batch_algorithm='"
                    +ui->comboBox_batch_algorithm->currentText().replace("'","''")
                    +"', data_loader_type='"
                    +ui->comboBox_data_loader_type->currentText().replace("'","''")
                    +"', description='"
                    +ui->lineEdit_description->text().replace("'","''")
                    +"', queue='"
                    +ui->lineEdit_queue->text().replace("'","''")
                    +"', max_network_kbps="
                    +QVariant(ui->spinBox_max_network_kbps->value()).toString().replace("'","''")
                    +" where channel_id = '"+channel_id.replace("'","''")+"';";
        manager->get(QNetworkRequest(QUrl(url)));
    }
}

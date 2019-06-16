#include "dialog_trigger.h"
#include "ui_dialog_trigger.h"
#include <QCompleter>

Dialog_trigger::Dialog_trigger(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_trigger)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));

}

Dialog_trigger::~Dialog_trigger()
{
    delete ui;
}

void Dialog_trigger::initialisation()
{
    QCompleter *cpl = new QCompleter(lst_table,this);
    ui->lineEdit_source_table_name->setCompleter(cpl);
    QCompleter *cpl_ch = new QCompleter(lst_channel_id,this);
    ui->lineEdit_channel_id->setCompleter(cpl_ch);
    bool *ok;
    if(data.count()>0){
        ui->lineEdit_trigger_id->setText(data.at(0));
        ui->lineEdit_source_catalog_name->setText(data.at(1));
        ui->lineEdit_source_schema_name->setText(data.at(2));
        ui->lineEdit_source_table_name->setText(data.at(3));
        ui->lineEdit_channel_id->setText(data.at(4));
        ui->lineEdit_reload_channel_id->setText(data.at(5));
        ui->spinBox_sync_on_update->setValue(QVariant(data.at(6)).toInt(ok));
        ui->spinBox_sync_on_insert->setValue(QVariant(data.at(7)).toInt(ok));
        ui->spinBox_sync_on_delete->setValue(QVariant(data.at(8)).toInt(ok));
        ui->spinBox_sync_on_incoming_batch->setValue(QVariant(data.at(9)).toInt(ok));
        ui->lineEdit_name_for_update_trigger->setText(data.at(10));
        ui->lineEdit_name_for_insert_trigger->setText(data.at(11));
        ui->lineEdit_name_for_delete_trigger->setText(data.at(12));
        ui->lineEdit_sync_on_update_condition->setText(data.at(13));
        ui->lineEdit_sync_on_insert_condition->setText(data.at(14));
        ui->lineEdit_sync_on_delete_condition->setText(data.at(15));
        ui->lineEdit_custom_before_update_text->setText(data.at(16));
        ui->lineEdit_custom_before_insert_text->setText(data.at(17));
        ui->lineEdit_custom_before_delete_text->setText(data.at(18));
        ui->lineEdit_custom_on_update_text->setText(data.at(19));
        ui->lineEdit_custom_on_insert_text->setText(data.at(20));
        ui->lineEdit_custom_on_delete_text->setText(data.at(21));
        ui->lineEdit_external_select->setText(data.at(22));
        ui->lineEdit_tx_id_expression->setText(data.at(23));
        ui->lineEdit_channel_expression->setText(data.at(24));
        ui->lineEdit_excluded_column_names->setText(data.at(25));
        ui->lineEdit_included_column_names->setText(data.at(26));
        ui->lineEdit_sync_key_names->setText(data.at(27));
        ui->spinBox_use_stream_lobs->setValue(QVariant(data.at(28)).toInt(ok));
        ui->spinBox_use_capture_lobs->setValue(QVariant(data.at(29)).toInt(ok));
        ui->spinBox_use_capture_old_data->setValue(QVariant(data.at(30)).toInt(ok));
        ui->spinBox_use_handle_key_updates->setValue(QVariant(data.at(31)).toInt(ok));
        ui->spinBox_stream_row->setValue(QVariant(data.at(32)).toInt(ok));
        ui->lineEdit_description->setText(data.at(36));
    }
}

void Dialog_trigger::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("executeQuery"))close();
    else if(response.contains("failed") | response.contains("error"))
        QMessageBox::information(this,"Error",response);
    else close();
}

void Dialog_trigger::on_pushButton_clicked()
{
    if(data.count()==0){
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query="
               + "INSERT INTO sym_trigger "
                +"(trigger_id, source_catalog_name, source_schema_name, source_table_name,"
                +" channel_id, reload_channel_id, sync_on_update, sync_on_insert, "
                +"sync_on_delete, sync_on_incoming_batch, name_for_update_trigger, "
                +"name_for_insert_trigger, name_for_delete_trigger, sync_on_update_condition,"
                + "sync_on_insert_condition, sync_on_delete_condition, custom_before_update_text, "
                +"custom_before_insert_text, custom_before_delete_text, custom_on_update_text, "
                +"custom_on_insert_text, custom_on_delete_text, external_select, tx_id_expression, "
                +"channel_expression, excluded_column_names, included_column_names, sync_key_names, "
               +" use_stream_lobs, use_capture_lobs, use_capture_old_data, use_handle_key_updates, "
                +"stream_row, create_time, last_update_by, last_update_time, description) "
                    +"VALUES('"
                    +ui->lineEdit_trigger_id->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_source_catalog_name->text().replace("'","''")
                +"', '"
                +ui->lineEdit_source_schema_name->text().replace("'","''")
                +"', '"
                +ui->lineEdit_source_table_name->text().replace("'","''")
                +"', '"
                +ui->lineEdit_channel_id->text().replace("'","''")
                +"', '"
                +ui->lineEdit_reload_channel_id->text().replace("'","''")
                +"', "
                +QVariant(ui->spinBox_sync_on_update->value()).toString().replace("'","''")
                +", "
                +QVariant(ui->spinBox_sync_on_insert->value()).toString().replace("'","''")
                +", "
                +QVariant(ui->spinBox_sync_on_delete->value()).toString().replace("'","''")
                +", "
                +QVariant(ui->spinBox_sync_on_incoming_batch->value()).toString().replace("'","''")
                +", '"
                +ui->lineEdit_name_for_update_trigger->text().replace("'","''")
                +"', '"
                +ui->lineEdit_name_for_insert_trigger->text().replace("'","''")
                +"', '"
                +ui->lineEdit_name_for_delete_trigger->text().replace("'","''")
                +"', '"
                +ui->lineEdit_sync_on_update_condition->text().replace("'","''")
                +"', '"
                +ui->lineEdit_sync_on_insert_condition->text().replace("'","''")
                +"', '"
                +ui->lineEdit_sync_on_delete_condition->text().replace("'","''")
                +"', '"
                +ui->lineEdit_custom_before_update_text->text().replace("'","''")
                +"', '"
                +ui->lineEdit_custom_before_insert_text->text().replace("'","''")
                +"', '"
                +ui->lineEdit_custom_before_delete_text->text().replace("'","''")
                +"', '"
                +ui->lineEdit_custom_on_update_text->text().replace("'","''")
                +"', '"
                +ui->lineEdit_custom_on_insert_text->text().replace("'","''")
                +"', '"
                +ui->lineEdit_custom_on_delete_text->text().replace("'","''")
                +"', '"
                +ui->lineEdit_external_select->text().replace("'","''")
                +"', '"
                +ui->lineEdit_tx_id_expression->text().replace("'","''")
                +"', '"
                +ui->lineEdit_channel_expression->text().replace("'","''")
                +"', '"
                +ui->lineEdit_excluded_column_names->text().replace("'","''")
                +"', '"
                +ui->lineEdit_included_column_names->text().replace("'","''")
                +"', '"
                +ui->lineEdit_sync_key_names->text().replace("'","''")
                +"', "
                +QVariant(ui->spinBox_use_stream_lobs->value()).toString().replace("'","''")
                +", "
                +QVariant(ui->spinBox_use_capture_lobs->value()).toString().replace("'","''")
                +", "
                +QVariant(ui->spinBox_use_capture_old_data->value()).toString().replace("'","''")
                +", "
                +QVariant(ui->spinBox_use_handle_key_updates->value()).toString().replace("'","''")
                +", "
                +QVariant(ui->spinBox_stream_row->value()).toString().replace("'","''")
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
                    +"/api/engine/querynode?query=UPDATE sym_trigger set trigger_id='"
                +ui->lineEdit_trigger_id->text().replace("'","''")
                +"', source_catalog_name='"
                +ui->lineEdit_source_catalog_name->text().replace("'","''")
            +"', source_schema_name='"
            +ui->lineEdit_source_schema_name->text().replace("'","''")
            +"', source_table_name='"
            +ui->lineEdit_source_table_name->text().replace("'","''")
            +"', channel_id='"
            +ui->lineEdit_channel_id->text().replace("'","''")
            +"', reload_channel_id='"
            +ui->lineEdit_reload_channel_id->text().replace("'","''")
            +"', sync_on_update="
            +QVariant(ui->spinBox_sync_on_update->value()).toString().replace("'","''")
            +", sync_on_insert="
            +QVariant(ui->spinBox_sync_on_insert->value()).toString().replace("'","''")
            +", sync_on_delete="
            +QVariant(ui->spinBox_sync_on_delete->value()).toString().replace("'","''")
            +", sync_on_incoming_batch="
            +QVariant(ui->spinBox_sync_on_incoming_batch->value()).toString().replace("'","''")
            +", name_for_update_trigger='"
            +ui->lineEdit_name_for_update_trigger->text().replace("'","''")
            +"', name_for_insert_trigger='"
            +ui->lineEdit_name_for_insert_trigger->text().replace("'","''")
            +"', name_for_delete_trigger='"
            +ui->lineEdit_name_for_delete_trigger->text().replace("'","''")
            +"', sync_on_update_condition='"
            +ui->lineEdit_sync_on_update_condition->text().replace("'","''")
            +"', sync_on_insert_condition='"
            +ui->lineEdit_sync_on_insert_condition->text().replace("'","''")
            +"', sync_on_delete_condition='"
            +ui->lineEdit_sync_on_delete_condition->text().replace("'","''")
            +"', custom_before_update_text='"
            +ui->lineEdit_custom_before_update_text->text().replace("'","''")
            +"', custom_before_insert_text='"
            +ui->lineEdit_custom_before_insert_text->text().replace("'","''")
            +"', custom_before_delete_text='"
            +ui->lineEdit_custom_before_delete_text->text().replace("'","''")
            +"', custom_on_update_text='"
            +ui->lineEdit_custom_on_update_text->text().replace("'","''")
            +"', custom_on_insert_text='"
            +ui->lineEdit_custom_on_insert_text->text().replace("'","''")
            +"', custom_on_delete_text='"
            +ui->lineEdit_custom_on_delete_text->text().replace("'","''")
            +"', external_select='"
            +ui->lineEdit_external_select->text().replace("'","''")
            +"', tx_id_expression='"
            +ui->lineEdit_tx_id_expression->text().replace("'","''")
            +"', channel_expression='"
            +ui->lineEdit_channel_expression->text().replace("'","''")
            +"', excluded_column_names='"
            +ui->lineEdit_excluded_column_names->text().replace("'","''")
            +"', included_column_names='"
            +ui->lineEdit_included_column_names->text().replace("'","''")
            +"', sync_key_names='"
            +ui->lineEdit_sync_key_names->text().replace("'","''")
            +"', use_stream_lobs="
            +QVariant(ui->spinBox_use_stream_lobs->value()).toString().replace("'","''")
            +", use_capture_lobs="
            +QVariant(ui->spinBox_use_capture_lobs->value()).toString().replace("'","''")
            +", use_capture_old_data="
            +QVariant(ui->spinBox_use_capture_old_data->value()).toString().replace("'","''")
            +", use_handle_key_updates="
            +QVariant(ui->spinBox_use_handle_key_updates->value()).toString().replace("'","''")
            +", stream_row="
            +QVariant(ui->spinBox_stream_row->value()).toString().replace("'","''")
            +", description='"
            +ui->lineEdit_description->text().replace("'","''")
            +"' where trigger_id = '"+trigger_id.replace("'","''")+"';";
        manager->get(QNetworkRequest(QUrl(url)));
    }

}

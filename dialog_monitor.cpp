#include "dialog_monitor.h"
#include "ui_dialog_monitor.h"

Dialog_monitor::Dialog_monitor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_monitor)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));

}

Dialog_monitor::~Dialog_monitor()
{
    delete ui;
}

void Dialog_monitor::initialisation()
{
    bool *ok;
    if(data.count()>0){
        ui->lineEdit_monitor_id->setText(data.at(0));
        ui->lineEdit_node_group_id->setText(data.at(1));
        ui->lineEdit_external_id->setText(data.at(2));
        ui->comboBox_type->setCurrentText(data.at(3));
        ui->plainTextEdit_expression->setPlainText(data.at(4));
        ui->spinBox_threshold->setValue(QVariant(data.at(5)).toInt(ok));
        ui->spinBox_run_period->setValue(QVariant(data.at(6)).toInt(ok));
        ui->spinBox_run_count->setValue(QVariant(data.at(7)).toInt(ok));
        ui->spinBox_severity_level->setValue(QVariant(data.at(8)).toInt(ok));
        ui->spinBox_enabled->setValue(QVariant(data.at(9)).toInt(ok));
    }
}

void Dialog_monitor::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("executeQuery") | response.contains("No results"))close();
    else if(response.contains("failed") | response.contains("error"))
        QMessageBox::information(this,"Error",response);
    else close();
}

void Dialog_monitor::on_pushButton_clicked()
{
    if(data.count()==0){
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query="
               + "INSERT INTO sym_monitor "
                +"(monitor_id, node_group_id, external_id, \"type\","
               +"  expression, threshold, run_period, run_count,"
               +" severity_level, enabled, create_time, last_update_by, last_update_time) "
                    +"VALUES('"
                    +ui->lineEdit_monitor_id->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_node_group_id->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_external_id->text().replace("'","''")
                    +"', '"
                    +ui->comboBox_type->currentText().replace("'","''")
                    +"', '"
                    +ui->plainTextEdit_expression->document()->toPlainText().replace("'","''")
                    +"', "
                    +QVariant(ui->spinBox_threshold->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_run_period->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_run_count->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_severity_level->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_enabled->value()).toString().replace("'","''")
                    +", current_timestamp, 'admin', current_timestamp);";
        manager->get(QNetworkRequest(QUrl(url)));
    }
    else{
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=UPDATE sym_monitor set monitor_id='"
                +ui->lineEdit_monitor_id->text().replace("'","''")
                +"', node_group_id='"
                +ui->lineEdit_node_group_id->text().replace("'","''")
                +"', \"type\"= '"
                +ui->comboBox_type->currentText().replace("'","''")
                +"', external_id='"
                +ui->lineEdit_external_id->text().replace("'","''")
                +"', expression='"
                +ui->plainTextEdit_expression->document()->toPlainText().replace("'","''")
                +"', threshold="
                +QVariant(ui->spinBox_threshold->value()).toString().replace("'","''")
                +", run_period="
                +QVariant(ui->spinBox_run_period->value()).toString().replace("'","''")
                +", run_count="
                +QVariant(ui->spinBox_run_count->value()).toString().replace("'","''")
                +", severity_level="
                +QVariant(ui->spinBox_severity_level->value()).toString().replace("'","''")
                +", enabled="
                +QVariant(ui->spinBox_enabled->value()).toString().replace("'","''")
                +" where monitor_id = '"+monitor_id.replace("'","''")+"';";
        manager->get(QNetworkRequest(QUrl(url)));
    }
}

#include "dialog_notification.h"
#include "ui_dialog_notification.h"

Dialog_notification::Dialog_notification(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_notification)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));

}

Dialog_notification::~Dialog_notification()
{
    delete ui;
}

void Dialog_notification::initialisation()
{
    bool *ok;
    if(data.count()>0){
        ui->lineEdit_notification_id->setText(data.at(0));
        ui->lineEdit_node_group_id->setText(data.at(1));
        ui->lineEdit_external_id->setText(data.at(2));
        ui->spinBox_severity_level->setValue(QVariant(data.at(3)).toInt(ok));
        ui->comboBox_type->setCurrentText(data.at(4));
        ui->plainTextEdit_expression->setPlainText(data.at(5));
        ui->spinBox_enabled->setValue(QVariant(data.at(6)).toInt(ok));
    }
}

void Dialog_notification::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("executeQuery"))close();
    else if(response.contains("failed") | response.contains("error"))
        QMessageBox::information(this,"Error",response);
    else close();
}

void Dialog_notification::on_pushButton_clicked()
{
    if(data.count()==0){
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query="
                "INSERT INTO sym_notification "
                "(notification_id, node_group_id, external_id, severity_level,"
                "  \"type\", expression, enabled, create_time, last_update_by, last_update_time)"
                +" VALUES('"
                +ui->lineEdit_notification_id->text().replace("'","''")
                +"', '"
                +ui->lineEdit_node_group_id->text().replace("'","''")
                +"', '"
                +ui->lineEdit_external_id->text().replace("'","''")
                +"', "
                +QVariant(ui->spinBox_severity_level->value()).toString().replace("'","''")
                +", '"
                +ui->comboBox_type->currentText().replace("'","''")
                +"', '"
                +ui->plainTextEdit_expression->document()->toPlainText().replace("'","''")
                +"', "
                +QVariant(ui->spinBox_enabled->value()).toString().replace("'","''")
                +", current_timestamp, 'admin', current_timestamp);";
        manager->get(QNetworkRequest(QUrl(url)));
    }
    else{
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=UPDATE sym_notification set notification_id='"
                +ui->lineEdit_notification_id->text().replace("'","''")
                +"', node_group_id='"
                +ui->lineEdit_node_group_id->text().replace("'","''")
                +"', external_id='"
                +ui->lineEdit_external_id->text().replace("'","''")
                +"', severity_level="
                +QVariant(ui->spinBox_severity_level->value()).toString()
                +", \"type\"='"
                +ui->comboBox_type->currentText().replace("'","''")
                +"', expression='"
                +ui->plainTextEdit_expression->document()->toPlainText().replace("'","''")
                +"', enabled="
                +QVariant(ui->spinBox_enabled->value()).toString().replace("'","''")
                    +" where notification_id = '"+notification_id.replace("'","''")+"';";
        manager->get(QNetworkRequest(QUrl(url)));
    }
}

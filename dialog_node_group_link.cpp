#include "dialog_node_group_link.h"
#include "ui_dialog_node_group_link.h"
#include <QCompleter>

Dialog_node_group_link::Dialog_node_group_link(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_node_group_link)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));

}

Dialog_node_group_link::~Dialog_node_group_link()
{
    delete ui;
}

void Dialog_node_group_link::initialisation()
{
    QCompleter *cpl = new QCompleter(lst_node_group,this);
    ui->lineEdit_source_node_group_id->setCompleter(cpl);
    ui->lineEdit_target_node_group_id->setCompleter(cpl);
    if(data.count()>0){
        bool *ok;
        ui->lineEdit_source_node_group_id->setText(data.at(0));
        ui->lineEdit_target_node_group_id->setText(data.at(1));
        ui->comboBox_data_event_action->setCurrentText(data.at(2));
        ui->spinBox_sync_config_enabled->setValue(QVariant(data.at(3)).toInt(ok));
        ui->spinBox_is_reversible->setValue(QVariant(data.at(4)).toInt(ok));
    }

}

void Dialog_node_group_link::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("executeQuery") | response.contains("No results"))close();
    else if(response.contains("failed") | response.contains("error"))
        QMessageBox::information(this,"Error",response);
    else close();
}

void Dialog_node_group_link::on_pushButton_clicked()
{
    if(data.count()==0){
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=INSERT INTO sym_node_group_link "
                    +"(source_node_group_id, target_node_group_id, data_event_action, sync_config_enabled, is_reversible) "
                    +"VALUES('"
                    +ui->lineEdit_source_node_group_id->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_target_node_group_id->text().replace("'","''")
                    +"', '"
                    +ui->comboBox_data_event_action->currentText().replace("'","''")
                    +"', "
                    +QVariant(ui->spinBox_sync_config_enabled->value()).toString().replace("'","''")
                    +", "
                    +QVariant(ui->spinBox_is_reversible->value()).toString().replace("'","''")
                    +");";
        manager->get(QNetworkRequest(QUrl(url)));
    }
    else{
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=UPDATE sym_node_group_link set source_node_group_id='"
                    +ui->lineEdit_source_node_group_id->text().replace("'","''")
                    +"', target_node_group_id='"
                    +ui->lineEdit_target_node_group_id->text().replace("'","''")
                    +"', data_event_action='"
                    +ui->comboBox_data_event_action->currentText().replace("'","''")
                    +"', sync_config_enabled="
                    +QVariant(ui->spinBox_sync_config_enabled->value()).toString().replace("'","''")
                    +", is_reversible="
                    +QVariant(ui->spinBox_is_reversible->value()).toString().replace("'","''")
                    +" where source_node_group_id = '"+source_node_group_id.replace("'","''")+"'  and target_node_group_id = '"+target_node_group_id.replace("'","''")+"';";
        manager->get(QNetworkRequest(QUrl(url)));
    }

}

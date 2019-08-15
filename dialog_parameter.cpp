#include "dialog_parameter.h"
#include "ui_dialog_parameter.h"
#include <QCompleter>
Dialog_parameter::Dialog_parameter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_parameter)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));

}

Dialog_parameter::~Dialog_parameter()
{
    delete ui;
}

void Dialog_parameter::initialisation()
{
    //bool *ok;
    QCompleter *cpl_nd = new QCompleter(lst_node_group, this);
    ui->lineEdit_node_group_id->setCompleter(cpl_nd);
    QCompleter *cpl_ext = new QCompleter(lst_external_id, this);
    ui->lineEdit_external_id->setCompleter(cpl_ext);
    if(data.count()>0){
        ui->lineEdit_external_id->setText(data.at(0));
        ui->lineEdit_node_group_id->setText(data.at(1));
        ui->lineEdit_param_key->setText(data.at(2));
        ui->plainTextEdit_param_value->setPlainText(data.at(3));
    }

}

void Dialog_parameter::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("executeQuery") | response.contains("No results"))close();
    else if(response.contains("failed") | response.contains("error"))
        QMessageBox::information(this,"Error",response);
    else close();
}

void Dialog_parameter::on_pushButton_clicked()
{
    if(data.count()==0){
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query="
                "INSERT INTO sym_parameter "
                "(external_id, node_group_id, param_key, "
                "param_value, create_time, last_update_by, last_update_time)"
                    +"VALUES('"
                    +ui->lineEdit_external_id->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_node_group_id->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_param_key->text().replace("'","''")
                    +"', '"
                    +ui->plainTextEdit_param_value->document()->toPlainText().replace("'","''")
                    +"', current_timestamp, 'admin', current_timestamp);";
        manager->get(QNetworkRequest(QUrl(url)));
    }
    else{
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=UPDATE sym_parameter set external_id='"
                +ui->lineEdit_external_id->text().replace("'","''")
                +"', node_group_id='"
                +ui->lineEdit_node_group_id->text().replace("'","''")
                +"', param_key='"
                +ui->lineEdit_param_key->text().replace("'","''")
                +"', param_value='"
                +ui->plainTextEdit_param_value->document()->toPlainText().replace("'","''")
                +"' where external_id = '"+external_id.replace("'","''")+"' and node_group_id = '"+node_group_id.replace("'","''")+"' and param_key = '"+param_key.replace("'","''")+"';";
        manager->get(QNetworkRequest(QUrl(url)));
    }
}

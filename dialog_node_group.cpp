#include "dialog_node_group.h"
#include "ui_dialog_node_group.h"

Dialog_node_group::Dialog_node_group(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_node_group)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));
}

Dialog_node_group::~Dialog_node_group()
{
    delete ui;
}

void Dialog_node_group::initialisation()
{
    if(data.count()>0){
        ui->lineEdit_node_group_id->setText(data.at(0));
        ui->lineEdit_description->setText(data.at(1));
    }
}

void Dialog_node_group::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    if(response.contains("executeQuery") | response.contains("No results"))close();
    else if(response.contains("failed") | response.contains("error"))
        QMessageBox::information(this,"Error",response);
    else close();
}

void Dialog_node_group::on_pushButton_clicked()
{
    if(data.count()==0){
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=INSERT INTO sym_node_group "
                    +"(node_group_id, description) "
                    +"VALUES('"
                    +ui->lineEdit_node_group_id->text().replace("'","''")
                    +"', '"
                    +ui->lineEdit_description->text().replace("'","''")
                    +"');";
        manager->get(QNetworkRequest(QUrl(url)));
    }
    else{
        QString url = "http://"
                    +host
                    +":"
                    +port
                    +"/api/engine/querynode?query=UPDATE sym_node_group set node_group_id='"
                    +ui->lineEdit_node_group_id->text().replace("'","''")
                    +"', description='"
                    +ui->lineEdit_description->text().replace("'","''")
                    +"' where node_group_id = '"+node_group_id+"';";
        manager->get(QNetworkRequest(QUrl(url)));
    }
}

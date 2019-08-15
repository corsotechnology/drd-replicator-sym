#include "dialog_open_registeration_node.h"
#include "ui_dialog_open_registeration_node.h"

Dialog_open_registeration_node::Dialog_open_registeration_node(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_open_registeration_node)
{
    ui->setupUi(this);
    QTimer::singleShot(200, this, SLOT(initialisation()));
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(managerFinished(QNetworkReply*)));
}

Dialog_open_registeration_node::~Dialog_open_registeration_node()
{
    delete ui;
}

void Dialog_open_registeration_node::on_pushButton_clicked()
{
    QString url("http://"
                +host
                +":"
                +port
                +"/api/engine/registernode");
    QByteArray data;
    data.append("externalId="
                +ui->lineEdit_externalId->text().replace("'","''")
                );
    manager->post(QNetworkRequest(QUrl(url)),data);
}

void Dialog_open_registeration_node::initialisation()
{

}

void Dialog_open_registeration_node::managerFinished(QNetworkReply *reply)
{
    QString response(reply->readAll());
    //--Debug
    QMessageBox::information(this,"Error",response);
    //---
    if(response.contains("failed") | response.contains("error")){
        QMessageBox::information(this,"Error",response);
        return;
    }
    else {
        QMessageBox::information(this,"Info","Request succeful.\n"+response);
        close();
    }
}

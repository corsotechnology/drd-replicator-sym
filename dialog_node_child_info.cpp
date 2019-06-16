#include "dialog_node_child_info.h"
#include "ui_dialog_node_child_info.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QTimer>

Dialog_node_child_info::Dialog_node_child_info(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_node_child_info)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE","CHILD-"+QVariant(rand()+rand()).toString());
    db.setDatabaseName("projects.db");
    if (!db.open())
       {
          QMessageBox::information(this,"Projects DB-Error",db.lastError().text());
          close();
       }
    QTimer::singleShot(200, this, SLOT(initialisation()));
}

Dialog_node_child_info::~Dialog_node_child_info()
{
    delete ui;
}

void Dialog_node_child_info::initialisation()
{
    ui->label_node_id->setText("Node ID : "+node_id);
}

void Dialog_node_child_info::on_pushButton_clicked()
{
    QSqlQuery qr(db);
    qr.prepare("update nodes set host='"+ui->lineEdit_host->text()+"', port="+QVariant(ui->spinBox_port->value()).toString()+" where nodeid='"+node_id+"' and project_id ="+project_id+";");
    if (!qr.exec())
       {
          QMessageBox::information(this,"Connection info DB-Error",qr.lastError().text());
          return;
       }
    close();
}

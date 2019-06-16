#include "dialog_new_project.h"
#include "ui_dialog_new_project.h"

Dialog_new_project::Dialog_new_project(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_new_project)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE","NEWPRO-"+QVariant(rand()+rand()).toString());
    db.setDatabaseName("projects.db");
    if (!db.open())
       {
          QMessageBox::information(this,"Projects DB-Error",db.lastError().text());
          close();
       }
}

Dialog_new_project::~Dialog_new_project()
{
    delete ui;
}

void Dialog_new_project::on_pushButton_save_clicked()
{
    if(ui->lineEdit_host->text().isEmpty() | ui->lineEdit_name->text().isEmpty()){
        QMessageBox::information(this,"Error","Fields must be filled with values");
        return;
    }
    QSqlQuery qr(db);
    qr.prepare("insert into project(name, host, port) values(:name, :host, :port);");
    qr.bindValue(":name",ui->lineEdit_name->text());
    qr.bindValue(":host",ui->lineEdit_host->text());
    qr.bindValue(":port",ui->spinBox_port->value());
    if (!qr.exec())
       {
          QMessageBox::information(this,"New Project DB-Error",qr.lastError().text());
          return;
       }
    close();
}

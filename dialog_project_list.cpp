#include "dialog_project_list.h"
#include "ui_dialog_project_list.h"
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QTimer>

Dialog_project_list::Dialog_project_list(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_project_list)
{
    ui->setupUi(this);
    QAction *sup_pro = new QAction(this);
    sup_pro->setText("Remove project");
    connect(sup_pro, &QAction::triggered, this, &Dialog_project_list::Sup_project);
    ui->tableView->addAction(sup_pro);
    db = QSqlDatabase::addDatabase("QSQLITE","CHILD-"+QVariant(rand()+rand()).toString());
    db.setDatabaseName("projects.db");
    if (!db.open())
       {
          QMessageBox::information(this,"Projects DB-Error",db.lastError().text());
          close();
       }
    QTimer::singleShot(300,this,SLOT(Display_projects()));
}

Dialog_project_list::~Dialog_project_list()
{
    delete ui;
}

void Dialog_project_list::Display_projects()
{
    QSqlQueryModel *mdl = new QSqlQueryModel();
    mdl->setQuery("select name from project;",db);
    ui->tableView->setModel(mdl);
    ui->tableView->setColumnWidth(0,ui->tableView->width());
}

void Dialog_project_list::Sup_project()
{
    QItemSelectionModel *selectionmodel = ui->tableView->selectionModel();
    QModelIndexList indexes = selectionmodel->selectedIndexes();
    QModelIndex index;
    if (indexes.isEmpty())return;
    int row=0;
    foreach(index, indexes)row = index.row();
    QAbstractItemModel *mdl =  ui->tableView->model();
    QString pro_name = mdl->index(row,0,QModelIndex()).data(Qt::EditRole).toString();
    QSqlQuery qr(db);
    qr.prepare("delete from project where name = :name;");
    qr.bindValue(":name",pro_name);
    if (!qr.exec())
       {
          QMessageBox::information(this,"Projects DB-Error",qr.lastError().text());
          return;
       }
    Display_projects();
}

void Dialog_project_list::on_pushButton_exit_clicked()
{
    is_exit = true;
    db.close();
    close();
}

void Dialog_project_list::on_tableView_doubleClicked(const QModelIndex &index)
{
    selected_pro=index.data(Qt::EditRole).toString();
    close();
}

void Dialog_project_list::on_pushButton_new_clicked()
{
    Dialog_new_project dl(this);
    dl.exec();
    Display_projects();
}

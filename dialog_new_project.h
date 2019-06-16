#ifndef DIALOG_NEW_PROJECT_H
#define DIALOG_NEW_PROJECT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

namespace Ui {
class Dialog_new_project;
}

class Dialog_new_project : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_new_project(QWidget *parent = nullptr);
    ~Dialog_new_project();
    QSqlDatabase db;

private slots:
    void on_pushButton_save_clicked();

private:
    Ui::Dialog_new_project *ui;
};

#endif // DIALOG_NEW_PROJECT_H

#ifndef DIALOG_PROJECT_LIST_H
#define DIALOG_PROJECT_LIST_H

#include <QDialog>
#include <QSqlDatabase>
#include "dialog_new_project.h"
#include <QAction>

namespace Ui {
class Dialog_project_list;
}

class Dialog_project_list : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_project_list(QWidget *parent = nullptr);
    ~Dialog_project_list();
    QSqlDatabase db;
    bool is_exit = false;
    QString selected_pro = "";


private slots:

    void Display_projects();

    void Sup_project();

    void on_pushButton_exit_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_new_clicked();

private:
    Ui::Dialog_project_list *ui;
};

#endif // DIALOG_PROJECT_LIST_H

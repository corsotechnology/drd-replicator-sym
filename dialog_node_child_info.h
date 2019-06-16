#ifndef DIALOG_NODE_CHILD_INFO_H
#define DIALOG_NODE_CHILD_INFO_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class Dialog_node_child_info;
}

class Dialog_node_child_info : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_node_child_info(QWidget *parent = nullptr);
    ~Dialog_node_child_info();
    QSqlDatabase db;
    QString node_id, project_id;

public slots:
    void initialisation();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Dialog_node_child_info *ui;
};

#endif // DIALOG_NODE_CHILD_INFO_H

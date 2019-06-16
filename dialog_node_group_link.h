#ifndef DIALOG_NODE_GROUP_LINK_H
#define DIALOG_NODE_GROUP_LINK_H

#include <QDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_node_group_link;
}

class Dialog_node_group_link : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_node_group_link(QWidget *parent = nullptr);
    ~Dialog_node_group_link();
    Ui::Dialog_node_group_link *ui;
    QStringList data,lst_node_group;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString source_node_group_id,target_node_group_id,host,port;
public slots:
    void initialisation();
    void managerFinished(QNetworkReply *reply);


private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_NODE_GROUP_LINK_H

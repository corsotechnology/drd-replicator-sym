#ifndef DIALOG_NODE_GROUP_H
#define DIALOG_NODE_GROUP_H

#include <QDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_node_group;
}

class Dialog_node_group : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_node_group(QWidget *parent = nullptr);
    ~Dialog_node_group();
    Ui::Dialog_node_group *ui;
    QStringList data;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString node_group_id,host,port;

public slots:
    void initialisation();
    void managerFinished(QNetworkReply *reply);

private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_NODE_GROUP_H

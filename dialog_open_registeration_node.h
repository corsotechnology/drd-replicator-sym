#ifndef DIALOG_OPEN_REGISTERATION_NODE_H
#define DIALOG_OPEN_REGISTERATION_NODE_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_open_registeration_node;
}

class Dialog_open_registeration_node : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_open_registeration_node(QWidget *parent = nullptr);
    ~Dialog_open_registeration_node();
    Ui::Dialog_open_registeration_node *ui;
    QString host,port;
    QStringList external_ids,node_group_ids;
    QNetworkAccessManager *manager;
    QNetworkRequest request;

private slots:
    void on_pushButton_clicked();
    void initialisation();
    void managerFinished(QNetworkReply *reply);

private:

};

#endif // DIALOG_OPEN_REGISTERATION_NODE_H

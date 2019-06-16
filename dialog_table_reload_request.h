#ifndef DIALOG_TABLE_RELOAD_REQUEST_H
#define DIALOG_TABLE_RELOAD_REQUEST_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_table_reload_request;
}

class Dialog_table_reload_request : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_table_reload_request(QWidget *parent = nullptr);
    ~Dialog_table_reload_request();
    Ui::Dialog_table_reload_request *ui;
    QString source_node_id,host,port;
    QStringList target_node_ids;
    QNetworkAccessManager *manager;
    QNetworkRequest request;


private slots:
    void on_pushButton_clicked();
    void initialisation();
    void managerFinished(QNetworkReply *reply);
};

#endif // DIALOG_TABLE_RELOAD_REQUEST_H

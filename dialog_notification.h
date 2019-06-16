#ifndef DIALOG_NOTIFICATION_H
#define DIALOG_NOTIFICATION_H

#include <QDebug>
#include <QDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_notification;
}

class Dialog_notification : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_notification(QWidget *parent = nullptr);
    ~Dialog_notification();
    Ui::Dialog_notification *ui;
    QStringList data;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString notification_id,host,port;

public slots:
    void initialisation();
    void managerFinished(QNetworkReply *reply);


private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_NOTIFICATION_H

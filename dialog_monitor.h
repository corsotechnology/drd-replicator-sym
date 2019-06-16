#ifndef DIALOG_MONITOR_H
#define DIALOG_MONITOR_H

#include <QDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_monitor;
}

class Dialog_monitor : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_monitor(QWidget *parent = nullptr);
    ~Dialog_monitor();
    Ui::Dialog_monitor *ui;
    QStringList data;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString monitor_id,host,port;

public slots:
    void initialisation();
    void managerFinished(QNetworkReply *reply);


private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_MONITOR_H

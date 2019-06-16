#ifndef DIALOG_CHANNEL_H
#define DIALOG_CHANNEL_H

#include <QDebug>
#include <QDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_channel;
}

class Dialog_channel : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_channel(QWidget *parent = nullptr);
    ~Dialog_channel();
    Ui::Dialog_channel *ui;
    QStringList data;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString channel_id,host,port,master_dbms;


public slots:
    void initialisation();
    void managerFinished(QNetworkReply *reply);

private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_CHANNEL_H

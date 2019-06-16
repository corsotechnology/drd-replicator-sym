#ifndef DIALOG_TRIGGER_ROUTER_H
#define DIALOG_TRIGGER_ROUTER_H

#include <QDebug>
#include <QDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_trigger_router;
}

class Dialog_trigger_router : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_trigger_router(QWidget *parent = nullptr);
    ~Dialog_trigger_router();
    Ui::Dialog_trigger_router *ui;
    QStringList data,lst_trigger_id,lst_router_id;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString trigger_id, router_id,host,port;

public slots:
    void initialisation();
    void managerFinished(QNetworkReply *reply);


private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_TRIGGER_ROUTER_H

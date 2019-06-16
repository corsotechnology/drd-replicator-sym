#ifndef DIALOG_ROUTER_H
#define DIALOG_ROUTER_H

#include <QDebug>
#include <QDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_router;
}

class Dialog_router : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_router(QWidget *parent = nullptr);
    ~Dialog_router();
    Ui::Dialog_router *ui;
    QStringList data;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString router_id,host,port;

public slots:
    void initialisation();
    void managerFinished(QNetworkReply *reply);

private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_ROUTER_H

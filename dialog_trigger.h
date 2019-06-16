#ifndef DIALOG_TRIGGER_H
#define DIALOG_TRIGGER_H

#include <QDebug>
#include <QDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_trigger;
}

class Dialog_trigger : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_trigger(QWidget *parent = nullptr);
    ~Dialog_trigger();
    Ui::Dialog_trigger *ui;
    QStringList data,lst_table,lst_channel_id;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString trigger_id,host,port;

public slots:
    void initialisation();
    void managerFinished(QNetworkReply *reply);

private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_TRIGGER_H

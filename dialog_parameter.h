#ifndef DIALOG_PARAMETER_H
#define DIALOG_PARAMETER_H

#include <QDialog>
#include <QStringList>
#include <QMessageBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Ui {
class Dialog_parameter;
}

class Dialog_parameter : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_parameter(QWidget *parent = nullptr);
    ~Dialog_parameter();
    Ui::Dialog_parameter *ui;
    QStringList data,lst_node_group,lst_external_id;
    QNetworkAccessManager *manager;
    QNetworkRequest request;
    QString external_id, node_group_id, param_key,host,port;

public slots:
    void initialisation();
    void managerFinished(QNetworkReply *reply);

private slots:
    void on_pushButton_clicked();
};

#endif // DIALOG_PARAMETER_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialog_channel.h"
#include "dialog_node_group.h"
#include "dialog_node_group_link.h"
#include "dialog_router.h"
#include "dialog_trigger.h"
#include "dialog_trigger_router.h"
#include "dialog_notification.h"
#include "dialog_monitor.h"
#include "dialog_parameter.h"
#include "dialog_project_list.h"
#include "table_color.h"
#include "dialog_node_child_info.h"
#include "dialog_table_reload_request.h"
#include "dialog_open_registeration_node.h"
#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonParseError>
#include <QDebug>
#include <QFile>
#include <QStandardItemModel>
#include <QModelIndex>
#include <QAction>
#include <QMessageBox>
#include <QModelIndexList>
#include <QBrush>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QXmlStreamReader>
#include <QSqlQueryModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    QSqlDatabase db;
    QNetworkAccessManager *channel_manager,
    *node_manager,
    *node_group_manager,
    *node_group_link_manager,
    *router_manager,
    *trigger_manager,
    *trigger_router_manager,
    *notification_manager,
    *monitor_manager,
    *parameter_manager,
    *req_manager,
    *ch_status_manager,
    *out_bt_manager,
    *in_bt_manager,
    *child_out_bt_manager,
    *child_in_bt_manager,
    *query_db_manager,
    *out_metrics_manager,
    *completer_manager;
    QString req_op;
    bool manager_finish;
    int project_id;
    QNetworkRequest request;
    QString current_table;
    QString child_host,child_port;
    QString master_dbms="",master_nodeid;
    //-- Auto-completion lists
    QStringList lst_node_group,lst_table,lst_trigger,lst_router,lst_node_id,lst_external_id,lst_channel_id;
public slots:

    void Full_screen();
    void Display_configuration();
    void Display_administration();
    void Display_projects();
    void Display_node_child_info();
    void Get_node_ops();
    void Register_node();
    void Start_sym_service();
    void Stop_sym_service();
    void Sync_sym_triggers();
    void Drop_sym_triggers();
    void Set_child_host_info();
    void Get_bt_error_child();
    void Table_reload_request_server();
    void Table_reload_request_client();
    void Get_out_metrics();

    void channel_managerFinished(QNetworkReply *reply);
    void node_managerFinished(QNetworkReply *reply);
    void node_group_managerFinished(QNetworkReply *reply);
    void node_group_link_managerFinished(QNetworkReply *reply);
    void router_managerFinished(QNetworkReply *reply);
    void trigger_managerFinished(QNetworkReply *reply);
    void trigger_router_managerFinished(QNetworkReply *reply);
    void notification_managerFinished(QNetworkReply *reply);
    void monitor_managerFinished(QNetworkReply *reply);
    void parameter_managerFinished(QNetworkReply *reply);
    void req_managerFinished(QNetworkReply *reply);
    void ch_status_managerFinished(QNetworkReply *reply);
    void out_bt_managerFinished(QNetworkReply *reply);
    void in_bt_managerFinished(QNetworkReply *reply);
    void child_out_bt_managerFinished(QNetworkReply *reply);
    void child_in_bt_managerFinished(QNetworkReply *reply);
    void query_db_managerFinished(QNetworkReply *reply);
    void out_metrics_managerFinished(QNetworkReply *reply);
    void completer_managerFinished(QNetworkReply *reply);


private slots:
    void on_pushButton_connect_clicked();

    //--Config Filters
    void on_lineEdit_chennel_filter_textChanged(const QString &arg1);
    void on_lineEdit_node_filter_textChanged(const QString &arg1);
    void on_lineEdit_node_group_filter_textChanged(const QString &arg1);
    void on_lineEdit_node_group_link_filter_textChanged(const QString &arg1);
    void on_lineEdit_router_filter_textChanged(const QString &arg1);
    void on_lineEdit_trigger_filter_textChanged(const QString &arg1);
    void on_lineEdit_trigger_route_filter_textChanged(const QString &arg1);
    void on_lineEdit_notification_filter_textChanged(const QString &arg1);
    void on_lineEdit_monitor_filter_textChanged(const QString &arg1);
    void on_lineEdit_parameter_filter_textChanged(const QString &arg1);

    //--Config actions
    void add_channel();
    void modify_channel();
    void remove_channel();
    void refresh_channel();

    void refresh_node();

    void add_node_group();
    void modify_node_group();
    void remove_node_group();
    void refresh_node_group();

    void add_node_group_link();
    void modify_node_group_link();
    void remove_node_group_link();
    void refresh_node_group_link();

    void add_router();
    void modify_router();
    void remove_router();
    void refresh_router();

    void add_trigger();
    void modify_trigger();
    void remove_trigger();
    void refresh_trigger();

    void add_trigger_router();
    void modify_trigger_router();
    void remove_trigger_router();
    void refresh_trigger_router();

    void add_notification();
    void modify_notification();
    void remove_notification();
    void refresh_notification();

    void add_monitor();
    void modify_monitor();
    void remove_monitor();
    void refresh_monitor();

    void add_parameter();
    void modify_parameter();
    void remove_parameter();
    void refresh_parameter();

    void refresh_ch_status();
    void refresh_in_bt();
    void set_new_out_bt();
    void set_ok_in_bt();
    void refresh_out_bt();
    void child_set_new_out_bt();
    void child_set_ok_in_bt();
    void refresh_child_out_bt();
    void refresh_child_in_bt();




    void on_lineEdit_ch_status_filter_textChanged(const QString &arg1);

    void on_pushButton_query_db_clicked();


};

#endif // MAINWINDOW_H

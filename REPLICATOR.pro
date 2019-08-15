#-------------------------------------------------
#
# Project created by QtCreator 2018-12-25T17:26:46
#
#-------------------------------------------------

QT += core gui network sql widgets



TARGET = release/REPLICATOR
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialog_channel.cpp \
    dialog_node_group.cpp \
    dialog_node_group_link.cpp \
    dialog_router.cpp \
    dialog_trigger.cpp \
    dialog_trigger_router.cpp \
    dialog_notification.cpp \
    dialog_monitor.cpp \
    dialog_parameter.cpp \
    dialog_project_list.cpp \
    dialog_new_project.cpp \
    dialog_node_child_info.cpp \
    dialog_table_reload_request.cpp \
    dialog_open_registeration_node.cpp \
    dialog_about.cpp

HEADERS += \
        mainwindow.h \
    dialog_channel.h \
    dialog_node_group.h \
    dialog_node_group_link.h \
    dialog_router.h \
    dialog_trigger.h \
    dialog_trigger_router.h \
    dialog_notification.h \
    dialog_monitor.h \
    dialog_parameter.h \
    dialog_project_list.h \
    dialog_new_project.h \
    table_color.h \
    dialog_node_child_info.h \
    dialog_table_reload_request.h \
    dialog_open_registeration_node.h \
    dialog_about.h

FORMS += \
        mainwindow.ui \
    dialog_channel.ui \
    dialog_node_group.ui \
    dialog_node_group_link.ui \
    dialog_router.ui \
    dialog_trigger.ui \
    dialog_trigger_router.ui \
    dialog_notification.ui \
    dialog_monitor.ui \
    dialog_parameter.ui \
    dialog_project_list.ui \
    dialog_new_project.ui \
    dialog_node_child_info.ui \
    dialog_table_reload_request.ui \
    dialog_open_registeration_node.ui \
    dialog_about.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

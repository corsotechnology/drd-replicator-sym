#include "dialog_about.h"
#include "ui_dialog_about.h"

Dialog_about::Dialog_about(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_about)
{
    ui->setupUi(this);
}

Dialog_about::~Dialog_about()
{
    delete ui;
}

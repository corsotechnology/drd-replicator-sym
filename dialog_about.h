#ifndef DIALOG_ABOUT_H
#define DIALOG_ABOUT_H

#include <QDialog>

namespace Ui {
class Dialog_about;
}

class Dialog_about : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_about(QWidget *parent = nullptr);
    ~Dialog_about();

private:
    Ui::Dialog_about *ui;
};

#endif // DIALOG_ABOUT_H

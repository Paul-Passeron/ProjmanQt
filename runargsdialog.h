#ifndef RUNARGSDIALOG_H
#define RUNARGSDIALOG_H

#include <QDialog>

namespace Ui {
class RunArgsDialog;
}

class RunArgsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RunArgsDialog(QWidget *parent = nullptr);
    ~RunArgsDialog();

private:
    Ui::RunArgsDialog *ui;
};

#endif // RUNARGSDIALOG_H

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

std::string getArgs() const;
private:
    Ui::RunArgsDialog *ui;
};

#endif // RUNARGSDIALOG_H

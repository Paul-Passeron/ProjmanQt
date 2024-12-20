#include "runargsdialog.h"
#include "ui_runargsdialog.h"

RunArgsDialog::RunArgsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RunArgsDialog)
{
    ui->setupUi(this);
}

RunArgsDialog::~RunArgsDialog()
{
    delete ui;
}

std::string RunArgsDialog::getArgs() const
{
    return ui->lineEdit->text().toStdString();
}

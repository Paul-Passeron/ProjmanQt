#include "newrunconfigurationdialog.h"
#include "ui_newrunconfigurationdialog.h"

NewRunConfigurationDialog::NewRunConfigurationDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::NewRunConfigurationDialog) {
  ui->setupUi(this);
  setWindowTitle("New Run Configuration");
}

NewRunConfigurationDialog::~NewRunConfigurationDialog() { delete ui; }

RunConfiguration NewRunConfigurationDialog::getConfig() {
  RunConfiguration config(ui->lineEdit->text().toStdString(),
                          ui->lineEdit_2->text().toStdString(),
                          ui->checkBox->isChecked());
}

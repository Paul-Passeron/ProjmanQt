#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(std::string command, QWidget *parent)
    : QDialog(parent), ui(new Ui::SettingsDialog) {
  ui->setupUi(this);
  ui->lineEdit->setText(QString::fromStdString(command));
}

SettingsDialog::~SettingsDialog() { delete ui; }

std::string SettingsDialog::getEditor() {
  return ui->lineEdit->text().toStdString();
}

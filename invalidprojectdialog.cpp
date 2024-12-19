#include "invalidprojectdialog.h"
#include "language.h"
#include "languagemanager.h"
#include "ui_invalidprojectdialog.h"

InvalidProjectDialog::InvalidProjectDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::InvalidProjectDialog) {
  ui->setupUi(this);
  std::vector<Language *> languages = LanguageManager::getAllLanguages();
  for (const auto &lang : languages) {
    ui->comboBox->addItem(QString::fromStdString(lang->getName()));
  }
  setWindowTitle("Unrecognized Project");
}

Language *InvalidProjectDialog::getLang() {
  return LanguageManager::fromName(ui->comboBox->currentText().toStdString());
}

InvalidProjectDialog::~InvalidProjectDialog() { delete ui; }

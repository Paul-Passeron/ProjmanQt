#include "newprojectdialog.h"
#include "languagemanager.h"
#include "ui_newprojectdialog.h"
#include "utils.h"
#include <QFileDialog>

NewProjectDialog::NewProjectDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::NewProjectDialog) {
  ui->setupUi(this);
  ui->badPath->setText("This directory does not exist !"
                       "Please choose an existing directory.");
  ui->badPath->hide();
  // This is to be cross platform across Windows, MacOS and Linux
  QString home = QString::fromStdString(Utils::getHome().string());
  ui->path->setText(home);

  // Setting up the language combo box
  std::vector<Language *> languages = LanguageManager::getAllLanguages();
  for (const auto &lang : languages) {
    ui->language->addItem(QString::fromStdString(lang->getName()));
  }

  setWindowTitle("New Project");
}

NewProjectDialog::~NewProjectDialog() { delete ui; }

std::string NewProjectDialog::getProjectName() {
  return ui->projectName->text().toStdString();
}
std::string NewProjectDialog::NewProjectDialog::getProjectPath() {
  return ui->path->text().toStdString();
}
std::string NewProjectDialog::NewProjectDialog::getLanguageName() {
  return ui->language->currentText().toStdString();
}
std::string NewProjectDialog::NewProjectDialog::getDescription() {
  return ui->description->toPlainText().toStdString();
}
bool NewProjectDialog::getGit() { return ui->useGit->isChecked(); }

void NewProjectDialog::on_browse_clicked() {
  QString srcDir = ui->path->text();
  if (ui->badPath->isVisible()) {
    srcDir = QString::fromStdString(Utils::getHome().string());
  }
  QString dir = QFileDialog::getExistingDirectory(
      this, "Browse project path...", srcDir,
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  if (!dir.isEmpty()) {
    ui->path->setText(dir);
  }
}

void NewProjectDialog::on_path_textChanged(const QString &arg1) {
  (void)arg1;
  const QString dir_to_test = ui->path->text();
  const QFileInfo dir_info(dir_to_test);
  if (!dir_info.exists() || dir_info.isFile()) {
    ui->badPath->show();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
  } else {
    ui->badPath->hide();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
  }
}

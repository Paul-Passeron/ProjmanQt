#include "mainwindow.h"
#include "language.h"
#include "languagemanager.h"
#include "newprojectdialog.h"
#include "newrunconfigurationdialog.h"
#include "projectinfos.h"
#include "projectmanager.h"
#include "qmessagebox.h"
#include "qnamespace.h"
#include "runconfiguration.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include <QFileDialog>
#include <QFileSystemModel>
#include <QLabel>
#include <QMessageBox>
#include <QRegularExpression>
#include <QSortFilterProxyModel>
#include <filesystem>
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  if (projectManager.getCurrentProject() == nullptr) {
    ui->treeView->setEnabled(false);
  }
  connect(&projectManager, &ProjectManager::currentProjectChanged, this,
          &MainWindow::on_currentProjectChanged);
  ui->searchBar->setVisible(false);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionExit_triggered() { QApplication::quit(); }

void MainWindow::on_actionNew_Project_triggered() {
  NewProjectDialog *dialog = new NewProjectDialog;
  if (dialog->exec() != QDialog::Accepted) {
    return;
  }
  std::string projectName = dialog->getProjectName();
  std::string description = dialog->getDescription();
  std::string projectPath = dialog->getProjectPath();
  std::string languageName = dialog->getLanguageName();
  bool useGit = dialog->getGit();
  Language *l = LanguageManager::fromName(languageName);
  printf("Language name: %s\n", l->getName().c_str());
  Project *proj =
      projectManager.fromLanguage(l, projectName, description, projectPath);
  proj->generateFileStructure();
  projectManager.createProject(proj);
  projectManager.setCurrentProject(proj->getName());
  std::filesystem::path full_path = proj->getPath() / proj->getSanitized();
  if (useGit) {
    Utils::initGit(full_path);
  }
  if (!description.empty()) {
    std::filesystem::path readme = full_path / "README.md";
    Utils::createFile(readme);
    std::ofstream file(readme);
    file << description;
    file.close();
  }
}

void MainWindow::on_currentProjectChanged() {

  Project *p = projectManager.getCurrentProject();
  ui->searchBar->setVisible(true);
  ui->projectOpenedLabel->setText(QString::fromStdString(p->getName()));
  ui->treeView->setEnabled(true);
  updateTreeView();
  p->serialize();
  if (infos != nullptr) {
    infos->update(p);
  } else {
    infos = new ProjectInfos(p);
    ui->horizontalLayout->addWidget(infos);
  }
}

void MainWindow::updateTreeView() {
  Project *project = projectManager.getCurrentProject();
  if (project == nullptr) {
    return;
  }
  std::filesystem::path projectPath = project->getPath();

  fileSystemModel = new QFileSystemModel;
  proxyModel = new QSortFilterProxyModel(this);
  fileSystemModel->setRootPath("/");
  proxyModel->setSourceModel(fileSystemModel);
  proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
  proxyModel->setRecursiveFilteringEnabled(true);
  connect(ui->searchBar, &QLineEdit::textChanged, this,
          &MainWindow::filterFiles);

  ui->treeView->setModel(proxyModel);
  auto index = fileSystemModel->index(
      QDir(projectPath / project->getSanitized()).absolutePath());
  ui->treeView->setRootIndex(proxyModel->mapFromSource(index));
}

void MainWindow::on_actionRun_Last_Configuration_triggered() {}

void MainWindow::on_actionOpen_Project_triggered() {
  QString dir = QFileDialog::getExistingDirectory(
      this, "Browse project path...", QDir::homePath(),
      QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
  std::filesystem::path p = dir.toStdString();
  if (!dir.isEmpty() && std::filesystem::exists(p)) {
    Project *project = projectManager.fromSerialized(p);
    if (project != nullptr) {
      projectManager.createProject(project);
      projectManager.setCurrentProject(project->getName());
    }
  }
}

void MainWindow::on_actionNew_Configuration_triggered() {
  auto diag = new NewRunConfigurationDialog();
  if (diag->exec() != QDialog::Accepted) {
    RunConfiguration config = diag->getConfig();
    Project *p = projectManager.getCurrentProject();
    if (p == nullptr) {
      return;
    }
    p->addRunConfiguration(config);
  }
}

void MainWindow::filterFiles(const QString &text) {
  // Set the filter regular expression

  proxyModel->setFilterRegularExpression(
      QRegularExpression(text, QRegularExpression::CaseInsensitiveOption));

  Project *project = projectManager.getCurrentProject();
  if (project == nullptr) {
    return;
  }
  std::filesystem::path projectPath = project->getPath();

  auto index = fileSystemModel->index(
      QDir(projectPath / project->getSanitized()).absolutePath());
  ui->treeView->setRootIndex(proxyModel->mapFromSource(index));
}

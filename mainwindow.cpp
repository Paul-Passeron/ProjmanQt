#include "mainwindow.h"
#include "language.h"
#include "languagemanager.h"
#include "newprojectdialog.h"
#include "newrunconfigurationdialog.h"
#include "projectinfos.h"
#include "projectmanager.h"
#include "qabstractitemmodel.h"
#include "qfilesystemmodel.h"
#include "qfilesystemwatcher.h"
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
#include <QTimer>
#include <filesystem>
#include <fstream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  if (projectManager.getCurrentProject() == nullptr) {
    ui->treeView->setEnabled(false);
  }
  connect(&projectManager, &ProjectManager::currentProjectChanged, this,
          &MainWindow::on_currentProjectChanged);
  ui->searchBar->setVisible(false);
  ui->pushButton->setVisible(false);
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
  ui->pushButton->setVisible(true);
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
  connect(p, &Project::runConfigurationsChanged, this,
          &MainWindow::on_RunConfigurationsChanged);
  on_RunConfigurationsChanged();
  std::filesystem::current_path(p->getPath() / p->getSanitized());
}

void MainWindow::reloadTreeView() {
  std::cout << "UPDATING ...." << std::endl;

  Project *project = projectManager.getCurrentProject();
  if (project == nullptr) {
    return;
  }
  std::filesystem::path projectPath = project->getPath();

  delete fileSystemModel;
  delete proxyModel;

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

void MainWindow::onTreeViewDoubleClicked(const QModelIndex &index) {
  if (!index.isValid()) {
    return; // Ensure the index is valid
  }
  QModelIndex sourceIndex = proxyModel->mapToSource(index);
  // Get the file path or item name from the model
  std::string filePath = fileSystemModel->filePath(sourceIndex).toStdString();

  if (externCommand.empty()) {
    externCommand = "code";
  }
  if (std::filesystem::is_regular_file(filePath)) {
    std::string command = externCommand + " " + filePath;
    int code;
    Utils::exec(command.c_str(), &code);
    // launching external editor
  }
}

void MainWindow::updateTreeView() {
  Project *project = projectManager.getCurrentProject();

  // Unfortunately, this does not work on every machine

  watcher.addPath(QString::fromStdString(
      (project->getPath() / project->getSanitized()).string()));
  connect(&watcher, &QFileSystemWatcher::directoryChanged, this,
          &MainWindow::reloadTreeView);

  connect(&watcher, &QFileSystemWatcher::fileChanged, this,
          &MainWindow::reloadTreeView);

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
  connect(ui->treeView, &QTreeView::doubleClicked, this,
          &MainWindow::onTreeViewDoubleClicked);
}

void MainWindow::on_actionRun_Last_Configuration_triggered() {
  Project *p = projectManager.getCurrentProject();
  if (p == nullptr) {
    QMessageBox::critical(
        this, "No Project Opened",
        "Please open or create a project before creating a run configuration.");
    return;
  }
  int rc = p->getLastConfig();
  if (rc < 0) {
    QMessageBox::critical(this, "No Last Configuration",
                          "Could not find last configuration");
    return;
  }
  ui->menuRun_Configuration->actions()[rc + 2]->trigger();
}

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

  Project *p = projectManager.getCurrentProject();
  if (p == nullptr) {
    QMessageBox::critical(
        this, "No Project Opened",
        "Please open or create a project before creating a run configuration.");
    return;
  }
  auto diag = new NewRunConfigurationDialog();
  if (diag->exec() != QDialog::Accepted) {
    return;
  }
  RunConfiguration config = diag->getConfig();
  p->addRunConfiguration(config);
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

void MainWindow::addRunConfiguration(RunConfiguration &rc) {
  QAction *runThisConfig = new QAction(QString::fromStdString(rc.getName()),
                                       ui->menuRun_Configuration);
  ui->menuRun_Configuration->addAction(runThisConfig);
  connect(runThisConfig, &QAction::triggered, &rc, &RunConfiguration::execute);
  connect(runThisConfig, &QAction::triggered, this, [&]() {
    Project *p = projectManager.getCurrentProject();
    if (p != nullptr) {
      p->setLastConfig(rc); // Set the last run configuration
    }
  });
}

void MainWindow::on_RunConfigurationsChanged() {
  int i = 0;
  for (auto action : ui->menuRun_Configuration->actions()) {
    i++;
    if (i > 2) {
      ui->menuRun_Configuration->removeAction(action);
    }
  }
  Project *project = projectManager.getCurrentProject();
  if (project == nullptr) {
    return;
  }
  std::vector<RunConfiguration> &configs = project->getConfigs();
  for (auto &config : configs) {
    addRunConfiguration(config);
  }
}
void MainWindow::on_pushButton_clicked() {
  if (projectManager.getCurrentProject() != nullptr) {
    reloadTreeView();
  }
}

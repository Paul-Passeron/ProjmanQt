#include "mainwindow.h"
#include "language.h"
#include "languagemanager.h"
#include "newprojectdialog.h"
#include "projectmanager.h"
#include "qmessagebox.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QMessageBox>

void dummyAction() {
  QMessageBox::information(nullptr, "Dummy", "This is a dummy action");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  if (projectManager.getCurrentProject() == nullptr) {
    QLabel *l =
        new QLabel("Create a new project or open a project to get started...");
    ui->treeView->setEnabled(false);
    ui->verticalLayout->insertWidget(0, l);
  }
  QAction *act = new QAction("Dummy\n", this);
  ui->menuRun_Configuration->addAction(act);
  connect(act, &QAction::triggered, this, &dummyAction);
  /*connect(&projectManager, &ProjectManager::currentProjectChanged, this,
          &MainWindow::on_currentProjectChanged);*/
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
  Project *proj = projectManager.fromLanguage(l, projectName, description);
  projectManager.createProject(proj);
  projectManager.setCurrentProject(proj->getName());
  //   projectManager.createProject(projectName, description, projectPath,
  //   useGit);
}

void MainWindow::on_currentProjectChanged() {
  QMessageBox msg;
  msg.setText(QString::fromStdString("Hello,World"));
  msg.exec();
}

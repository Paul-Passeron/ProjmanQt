#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "projectinfos.h"
#include "projectmanager.h"
#include "qfilesystemmodel.h"
#include "qsortfilterproxymodel.h"
#include "runconfiguration.h"
#include <QFileSystemWatcher>
#include <QLabel>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
  ProjectManager projectManager;

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void on_actionExit_triggered();

  void on_actionNew_Project_triggered();

  void on_currentProjectChanged();

  void on_actionRun_Last_Configuration_triggered();

  void on_actionOpen_Project_triggered();

  void on_actionNew_Configuration_triggered();

  void filterFiles(const QString &text);

  void on_RunConfigurationsChanged();

  void reloadTreeView();

  void on_pushButton_clicked();

  void onTreeViewDoubleClicked(const QModelIndex &index);

  void on_actionAbout_ProjmanQt_triggered();

  void on_actionBuild_triggered();

  void on_actionRun_triggered();

  void on_actionClean_triggered();

  private:
  Ui::MainWindow *ui;

  ProjectInfos *infos = nullptr;

  QFileSystemModel *fileSystemModel;

  QSortFilterProxyModel *proxyModel;

  QFileSystemWatcher watcher;

  std::string externCommand;

  void updateTreeView();

  void addRunConfiguration(RunConfiguration &rc);
};
#endif // MAINWINDOW_H

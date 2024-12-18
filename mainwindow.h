#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "projectmanager.h"
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

private:
  Ui::MainWindow *ui;

  void updateTreeView();
};
#endif // MAINWINDOW_H

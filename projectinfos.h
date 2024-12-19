#ifndef PROJECTINFOS_H
#define PROJECTINFOS_H

#include <QWidget>

class Project;

namespace Ui {
class ProjectInfos;
}

class ProjectInfos : public QWidget {
  Q_OBJECT
  Project *p;

public:
  explicit ProjectInfos(Project *p, QWidget *parent = nullptr);
  ~ProjectInfos();

  private slots:
  void on_pushButton_clicked();

  private:
  Ui::ProjectInfos *ui;
};

#endif // PROJECTINFOS_H
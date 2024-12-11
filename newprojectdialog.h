#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog {
  Q_OBJECT

public:
  explicit NewProjectDialog(QWidget *parent = nullptr);
  ~NewProjectDialog();
  std::string getProjectName();
  std::string getProjectPath();
  std::string getLanguageName();
  std::string getDescription();
  bool getGit();

  private slots:
  void on_browse_clicked();

      void on_path_textChanged(const QString &arg1);

  private:
  Ui::NewProjectDialog *ui;
};

#endif // NEWPROJECTDIALOG_H

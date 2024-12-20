#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog {
  Q_OBJECT

public:
  explicit SettingsDialog(std::string command, QWidget *parent = nullptr);
  ~SettingsDialog();
  std::string getEditor();

private:
  Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H

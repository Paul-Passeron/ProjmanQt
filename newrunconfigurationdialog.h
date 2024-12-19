#ifndef NEWRUNCONFIGURATIONDIALOG_H
#define NEWRUNCONFIGURATIONDIALOG_H
#include <QDialog>
#include <runconfiguration.h>

namespace Ui {
class NewRunConfigurationDialog;
}

class NewRunConfigurationDialog : public QDialog {
  Q_OBJECT

public:
  explicit NewRunConfigurationDialog(QWidget *parent = nullptr);
  ~NewRunConfigurationDialog();
  RunConfiguration getConfig();

private:
  Ui::NewRunConfigurationDialog *ui;
};

#endif // NEWRUNCONFIGURATIONDIALOG_H

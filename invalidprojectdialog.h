#ifndef INVALIDPROJECTDIALOG_H
#define INVALIDPROJECTDIALOG_H

#include "language.h"
#include <QDialog>

namespace Ui {
class InvalidProjectDialog;
}

class InvalidProjectDialog : public QDialog {
  Q_OBJECT

public:
  explicit InvalidProjectDialog(QWidget *parent = nullptr);
  ~InvalidProjectDialog();
  Language *getLang();

private:
  Ui::InvalidProjectDialog *ui;
};

#endif // INVALIDPROJECTDIALOG_H

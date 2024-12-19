#include "projectinfos.h"
#include "project.h"
#include "ui_projectinfos.h"
ProjectInfos::ProjectInfos(Project *p, QWidget *parent)
    : QWidget(parent), p(p), ui(new Ui::ProjectInfos) {
  ui->setupUi(this);
  ui->proj_name->setText(QString::fromStdString(p->getName()));
  ui->path->setText(
      QString::fromStdString((p->getPath() / p->getSanitized()).string()));
  ui->desc->setText(QString::fromStdString(p->getDescription()));
}

ProjectInfos::~ProjectInfos() { delete ui; }

void ProjectInfos::on_pushButton_clicked() {
  // Save
  p->serialize();
}
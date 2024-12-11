/********************************************************************************
** Form generated from reading UI file 'newprojectdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECTDIALOG_H
#define UI_NEWPROJECTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_NewProjectDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *projectName;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QLabel *label_2;
    QComboBox *language;
    QLabel *label_3;
    QTextEdit *textEdit;
    QLabel *label_4;
    QCheckBox *useGit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewProjectDialog)
    {
        if (NewProjectDialog->objectName().isEmpty())
            NewProjectDialog->setObjectName("NewProjectDialog");
        NewProjectDialog->resize(400, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NewProjectDialog->sizePolicy().hasHeightForWidth());
        NewProjectDialog->setSizePolicy(sizePolicy);
        formLayout = new QFormLayout(NewProjectDialog);
        formLayout->setObjectName("formLayout");
        label = new QLabel(NewProjectDialog);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        projectName = new QLineEdit(NewProjectDialog);
        projectName->setObjectName("projectName");

        formLayout->setWidget(0, QFormLayout::FieldRole, projectName);

        label_5 = new QLabel(NewProjectDialog);
        label_5->setObjectName("label_5");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        lineEdit = new QLineEdit(NewProjectDialog);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout->addWidget(lineEdit);

        pushButton = new QPushButton(NewProjectDialog);
        pushButton->setObjectName("pushButton");
        pushButton->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(pushButton);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        label_2 = new QLabel(NewProjectDialog);
        label_2->setObjectName("label_2");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        language = new QComboBox(NewProjectDialog);
        language->setObjectName("language");

        formLayout->setWidget(2, QFormLayout::FieldRole, language);

        label_3 = new QLabel(NewProjectDialog);
        label_3->setObjectName("label_3");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        textEdit = new QTextEdit(NewProjectDialog);
        textEdit->setObjectName("textEdit");

        formLayout->setWidget(3, QFormLayout::FieldRole, textEdit);

        label_4 = new QLabel(NewProjectDialog);
        label_4->setObjectName("label_4");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_4);

        useGit = new QCheckBox(NewProjectDialog);
        useGit->setObjectName("useGit");

        formLayout->setWidget(4, QFormLayout::FieldRole, useGit);

        buttonBox = new QDialogButtonBox(NewProjectDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        formLayout->setWidget(5, QFormLayout::FieldRole, buttonBox);


        retranslateUi(NewProjectDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, NewProjectDialog, qOverload<>(&QDialog::reject));
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, NewProjectDialog, qOverload<>(&QDialog::accept));

        QMetaObject::connectSlotsByName(NewProjectDialog);
    } // setupUi

    void retranslateUi(QDialog *NewProjectDialog)
    {
        NewProjectDialog->setWindowTitle(QCoreApplication::translate("NewProjectDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("NewProjectDialog", "Project Name", nullptr));
        label_5->setText(QCoreApplication::translate("NewProjectDialog", "Project Path", nullptr));
        pushButton->setText(QCoreApplication::translate("NewProjectDialog", "Browse", nullptr));
        label_2->setText(QCoreApplication::translate("NewProjectDialog", "Language", nullptr));
        label_3->setText(QCoreApplication::translate("NewProjectDialog", "Description", nullptr));
        label_4->setText(QCoreApplication::translate("NewProjectDialog", "Initialize Git", nullptr));
        useGit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class NewProjectDialog: public Ui_NewProjectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECTDIALOG_H

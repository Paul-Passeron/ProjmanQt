/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew_Project;
    QAction *actionOpen_Project;
    QAction *actionExit;
    QAction *actionBuild;
    QAction *actionRun;
    QAction *actionForce_Build;
    QAction *actionForce_Run;
    QAction *actionClean;
    QAction *actionInstall;
    QAction *actionNew_Configuration;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;
    QFormLayout *formLayout;
    QFrame *frame;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuProject;
    QMenu *menuRun_Configuration;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionNew_Project = new QAction(MainWindow);
        actionNew_Project->setObjectName("actionNew_Project");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::FolderNew));
        actionNew_Project->setIcon(icon);
        actionOpen_Project = new QAction(MainWindow);
        actionOpen_Project->setObjectName("actionOpen_Project");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::FolderOpen));
        actionOpen_Project->setIcon(icon1);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
        actionExit->setIcon(icon2);
        actionBuild = new QAction(MainWindow);
        actionBuild->setObjectName("actionBuild");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::ViewRefresh));
        actionBuild->setIcon(icon3);
        actionRun = new QAction(MainWindow);
        actionRun->setObjectName("actionRun");
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        actionRun->setIcon(icon4);
        actionForce_Build = new QAction(MainWindow);
        actionForce_Build->setObjectName("actionForce_Build");
        actionForce_Run = new QAction(MainWindow);
        actionForce_Run->setObjectName("actionForce_Run");
        actionClean = new QAction(MainWindow);
        actionClean->setObjectName("actionClean");
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::EditClear));
        actionClean->setIcon(icon5);
        actionInstall = new QAction(MainWindow);
        actionInstall->setObjectName("actionInstall");
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::SecurityHigh));
        actionInstall->setIcon(icon6);
        actionNew_Configuration = new QAction(MainWindow);
        actionNew_Configuration->setObjectName("actionNew_Configuration");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName("treeView");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(treeView);


        horizontalLayout->addLayout(verticalLayout);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);

        formLayout->setWidget(0, QFormLayout::LabelRole, frame);


        horizontalLayout->addLayout(formLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuProject = new QMenu(menubar);
        menuProject->setObjectName("menuProject");
        menuRun_Configuration = new QMenu(menubar);
        menuRun_Configuration->setObjectName("menuRun_Configuration");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuProject->menuAction());
        menubar->addAction(menuRun_Configuration->menuAction());
        menuFile->addAction(actionNew_Project);
        menuFile->addAction(actionOpen_Project);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuProject->addAction(actionBuild);
        menuProject->addAction(actionRun);
        menuProject->addAction(actionForce_Build);
        menuProject->addAction(actionForce_Run);
        menuProject->addAction(actionClean);
        menuProject->addAction(actionInstall);
        menuRun_Configuration->addAction(actionNew_Configuration);
        toolBar->addAction(actionNew_Project);
        toolBar->addAction(actionOpen_Project);
        toolBar->addSeparator();
        toolBar->addAction(actionBuild);
        toolBar->addAction(actionRun);
        toolBar->addAction(actionClean);
        toolBar->addAction(actionInstall);
        toolBar->addSeparator();
        toolBar->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionNew_Project->setText(QCoreApplication::translate("MainWindow", "New Project", nullptr));
        actionOpen_Project->setText(QCoreApplication::translate("MainWindow", "Open Project", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionBuild->setText(QCoreApplication::translate("MainWindow", "Build", nullptr));
        actionRun->setText(QCoreApplication::translate("MainWindow", "Run", nullptr));
#if QT_CONFIG(shortcut)
        actionRun->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        actionForce_Build->setText(QCoreApplication::translate("MainWindow", "Force Build", nullptr));
        actionForce_Run->setText(QCoreApplication::translate("MainWindow", "Force Run", nullptr));
        actionClean->setText(QCoreApplication::translate("MainWindow", "Clean", nullptr));
        actionInstall->setText(QCoreApplication::translate("MainWindow", "Install", nullptr));
        actionNew_Configuration->setText(QCoreApplication::translate("MainWindow", "New Configuration", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuProject->setTitle(QCoreApplication::translate("MainWindow", "Project", nullptr));
        menuRun_Configuration->setTitle(QCoreApplication::translate("MainWindow", "Run Configuration", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

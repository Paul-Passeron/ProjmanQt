QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buildsystem.cpp \
    clanguage.cpp \
    cpplanguage.cpp \
    cppproject.cpp \
    cproject.cpp \
    invalidprojectdialog.cpp \
    language.cpp \
    languagemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    makefilebuildsystem.cpp \
    newprojectdialog.cpp \
    newrunconfigurationdialog.cpp \
    project.cpp \
    projectinfos.cpp \
    projectmanager.cpp \
    projectserializer.cpp \
    pythonbuildsystem.cpp \
    pythonlanguage.cpp \
    pythonproject.cpp \
    runargsdialog.cpp \
    runconfiguration.cpp \
    settingsdialog.cpp \
    utils.cpp

HEADERS += \
    buildsystem.h \
    clanguage.h \
    cmakebuildsystem.h \
    cpplanguage.h \
    cppproject.h \
    cproject.h \
    invalidprojectdialog.h \
    javalanguage.h \
    language.h \
    languagemanager.h \
    mainwindow.h \
    makefilebuildsystem.h \
    newprojectdialog.h \
    newrunconfigurationdialog.h \
    project.h \
    projectinfos.h \
    projectmanager.h \
    projectserializer.h \
    pythonbuildsystem.h \
    pythonlanguage.h \
    pythonproject.h \
    runargsdialog.h \
    runconfiguration.h \
    settingsdialog.h \
    utils.h

FORMS += \
    invalidprojectdialog.ui \
    mainwindow.ui \
    newprojectdialog.ui \
    newrunconfigurationdialog.ui \
    projectinfos.ui \
    runargsdialog.ui \
    settingsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

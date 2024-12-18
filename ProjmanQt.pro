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
    javalanguage.cpp \
    language.cpp \
    languagemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    makefilebuildsystem.cpp \
    newprojectdialog.cpp \
    project.cpp \
    projectmanager.cpp \
    projectserializer.cpp \
    pythonlanguage.cpp \
    runconfiguration.cpp \
    utils.cpp

HEADERS += \
    buildsystem.h \
    clanguage.h \
    cmakebuildsystem.h \
    cpplanguage.h \
    cppproject.h \
    javalanguage.h \
    language.h \
    languagemanager.h \
    mainwindow.h \
    makefilebuildsystem.h \
    newprojectdialog.h \
    project.h \
    projectmanager.h \
    projectserializer.h \
    pythonlanguage.h \
    runconfiguration.h \
    utils.h

FORMS += \
    mainwindow.ui \
    newprojectdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

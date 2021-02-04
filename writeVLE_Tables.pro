#-------------------------------------------------
#
# Project created by QtCreator 2018-04-10T11:36:22
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport
RC_ICONS = ico.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = writeVLE_Tables
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        computeemp.cpp \
        computelea.cpp \
        dockread.cpp \
        empleatables.cpp \
        mainwindow.cpp \
        rowdialog.cpp \
        table1mdialog.cpp \
        table22dialog.cpp \
        table23dialog.cpp \
        table3bdialog.cpp \
        table3rdialog.cpp \
        tablescontroller.cpp

HEADERS  += \
    computeemp.h \
    computelea.h \
    dockread.h \
    empdata.h \
    empleatables.h \
    leadata.h \
    mainwindow.h \
    rowdialog.h \
    table1mdialog.h \
    table22dialog.h \
    table23dialog.h \
    table3bdialog.h \
    table3rdialog.h \
    tablescontroller.h

FORMS    += \
    dockread.ui \
    mainwindow.ui \
    rowdialog.ui \
    table1mdialog.ui \
    table22dialog.ui \
    table23dialog.ui \
    table3bdialog.ui \
    table3rdialog.ui

RESOURCES += \
    writeVLE_Tables.qrc

DISTFILES +=

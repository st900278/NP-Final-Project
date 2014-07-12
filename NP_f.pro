#-------------------------------------------------
#
# Project created by QtCreator 2014-06-22T23:22:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NP_f
TEMPLATE = app



SOURCES += \
    chatpanel.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    addfdialog.cpp \
    client.cpp

HEADERS  += \
    chatpanel.h \
    loginwindow.h \
    mainwindow.h \
    client.h \
    addfdialog.h

FORMS    += \
    chatpanel.ui \
    loginwindow.ui \
    mainwindow.ui \
    addfdialog.ui

RESOURCES += \
    pic.qrc

OTHER_FILES +=

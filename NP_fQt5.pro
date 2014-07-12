#-------------------------------------------------
#
# Project created by QtCreator 2014-06-24T00:20:00
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NP_fQt5
TEMPLATE = app
INCLUDEPATH += /usr/local/include/opencv
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib/
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_ml
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_calib3d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib
LIBS += -lopencv_legacy
LIBS += -lopencv_flann
LIBS += -lopencv_nonfree


SOURCES += main.cpp \
    addfdialog.cpp \
    chatpanel.cpp \
    client.cpp \
    loginwindow.cpp \
    mainwindow.cpp

HEADERS  += \
    addfdialog.h \
    chatpanel.h \
    client.h \
    loginwindow.h \
    mainwindow.h

FORMS    += \
    addfdialog.ui \
    chatpanel.ui \
    loginwindow.ui \
    mainwindow.ui

SUBDIRS += \
    NP_f.pro

RESOURCES += \
    icon.qrc \
    pic.qrc

OTHER_FILES += \
    NP_f.pro.user \
    NP_fQt5.pro.user

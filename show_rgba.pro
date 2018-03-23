#-------------------------------------------------
#
# Project created by QtCreator 2018-03-08T20:02:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = show_rgba
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../third_party

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    color_space.cpp \
    image_generate.cpp \
    x264_to_mp4.cpp \
    encode.cpp \
    work_flow.cpp

HEADERS += \
        mainwindow.h \
    color_space.h \
    image_generate.h \
    x264_to_mp4.h \
    observer.h \
    encode.h \
    work_flow.h

FORMS += \
        mainwindow.ui

LIBS += -L/usr/local/lib -lx264 -ldl -lpthread
LIBS += -lm -ldl -lpthread -lrt -lavcodec -lavformat -lavutil


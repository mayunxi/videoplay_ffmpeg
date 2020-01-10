#-------------------------------------------------
#
# Project created by QtCreator
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoPlayer
TEMPLATE = app


SOURCES += main.cpp \
    videoplayer.cpp \
    mainwindow.cpp

HEADERS  += \
    videoplayer.h \
    mainwindow.h

FORMS    += \
    mainwindow.ui

INCLUDEPATH += $$PWD/ffmpeg/include \
                $$PWD/src

#for linaro on rk3288
#LIBS += /usr/local/lib/libavformat.so \
#        /usr/local/lib/libavutil.so     \
#        /usr/local/lib/libavcodec.so   \
#        /usr/local/lib/libswscale.so    \
#        /usr/local/lib/libavdevice.so  \
#        /usr/local/lib/libavfilter.so   \
#        /usr/local/lib/libswresample.so

#for pi on rk3399
LIBS += /usr/lib/aarch64-linux-gnu/libavformat.so \
        /usr/lib/aarch64-linux-gnu/libavutil.so     \
        /usr/lib/aarch64-linux-gnu/libavcodec.so   \
        /usr/lib/aarch64-linux-gnu/libswscale.so    \
        /usr/lib/aarch64-linux-gnu/libavdevice.so.57  \
        /usr/lib/aarch64-linux-gnu/libavfilter.so.6   \
        /usr/lib/aarch64-linux-gnu/libswresample.so

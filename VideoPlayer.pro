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

LIBS += /usr/lib/arm-linux-gnueabihf/libopencv_highgui.so.2.4 \
        /usr/lib/arm-linux-gnueabihf/libopencv_core.so.2.4    \
        /usr/lib/arm-linux-gnueabihf/libopencv_imgproc.so.2.4 \
        /usr/lib/arm-linux-gnueabihf/libopencv_objdetect.so.2.4  \
        /usr/lib/arm-linux-gnueabihf/libopencv_video.so.2.4       \
        /usr/lib/arm-linux-gnueabihf/libopencv_calib3d.so.2.4  \
        /usr/local/lib/libavformat.so \
        /usr/local/lib/libavutil.so     \
        /usr/local/lib/libavcodec.so   \
        /usr/local/lib/libswscale.so    \
        /usr/local/lib/libavdevice.so  \
        /usr/local/lib/libavfilter.so   \
        /usr/local/lib/libswresample.so

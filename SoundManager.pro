#-------------------------------------------------
#
# Project created by QtCreator 2014-08-13T11:36:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoundManager
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow/MainWindow.cpp \
    Commons/Commons.cpp \
    WaveFile/WaveFile.cpp \
    WaveFile/Fourier.cpp \
    MainWindow/ChannelDataWidget.cpp \
    WaveFile/WavFileChannelVisualizer.cpp

HEADERS  += MainWindow/MainWindow.h \
    Commons/FileWrapper.h \
    Commons/Commons.h \
    WaveFile/WaveFileErrors.h \
    WaveFile/WaveFile.h \
    WaveFile/Fourier.h \
    MainWindow/ChannelDataWidget.h \
    WaveFile/WavFileChannelVisualizer.h

FORMS    += MainWindow/MainWindow.ui

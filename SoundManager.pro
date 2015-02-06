#-------------------------------------------------
#
# Project created by QtCreator 2014-08-13T11:36:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SoundManager
TEMPLATE = app

QMAKE_CFLAGS_WARN_ON -= -W3
QMAKE_CFLAGS_WARN_ON += -W4

SOURCES += main.cpp\
        MainWindow/MainWindow.cpp \
    Commons/Commons.cpp \
    WaveFile/WaveFile.cpp \
    WaveFile/Fourier.cpp \
    MainWindow/ChannelDataWidget.cpp \
    WaveFile/WavFileChannelVisualizer.cpp \
    MainWindow/ChannelSpectrogramWidget.cpp \
    WaveFile/WaveFileSpectrogramVisualizer.cpp

HEADERS  += MainWindow/MainWindow.h \
    Commons/FileWrapper.h \
    Commons/Commons.h \
    WaveFile/WaveFileErrors.h \
    WaveFile/WaveFile.h \
    WaveFile/Fourier.h \
    MainWindow/ChannelDataWidget.h \
    WaveFile/WavFileChannelVisualizer.h \
    MainWindow/ChannelSpectrogramWidget.h \
    WaveFile/WaveFileSpectrogramVisualizer.h \
    WaveFile/FFTWindow.h

FORMS    += MainWindow/MainWindow.ui

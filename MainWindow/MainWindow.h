#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "WaveFile/WaveFileErrors.h"
#include "WaveFile/WaveFile.h"
#include "WaveFile/WavFileChannelVisualizer.h"

namespace Ui {
  class MainWindow;
  }

class MainWindow : public QMainWindow {
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  
private:
  Ui::MainWindow *ui;

  CWavFile *m_wavFile;

  void ResetWavFile(const std::string& fileName);

private slots:
  void MnuFileExit_Clicked(void);
  void MnuFileOpen_Clicked(void);

};

#endif // MAINWINDOW_H

#include "MainWindow/MainWindow.h"
#include <QApplication>

#include "WaveFile/Fourier.h"
#include "WaveFile/WaveFile.h"

int main(int argc, char *argv[]) {  
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  
  return a.exec();
}

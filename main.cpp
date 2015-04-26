#include "MainWindow/MainWindow.h"
#include <QApplication>
#include <QDebug>
#include <memory>
#include <cstring>

int main(int argc, char *argv[]) {     
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}

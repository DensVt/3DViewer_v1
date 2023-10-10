#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  // setlocale(LC_ALL, "en_US.UTF-8");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}

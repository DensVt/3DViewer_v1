#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>

#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QRadioButton>
#include <QSettings>
#include <QTimer>
#include <cstring>

#include "glwidget.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_action_triggered();

  void slotTimer();

  void on_moove_y_plus();

  void on_moove_y_sub();

  void on_moove_x_sub();

  void on_moove_x_plus();

  void on_scale_plus();

  void on_scale_sub();

  void on_background_color_menu();

  void on_line_color_menu();

  void on_dot_color_menu();

  void on_line_size_plus();

  void on_line_size_sub();

  void on_line_mode(int index);

  void on_point_size_s();

  void on_point_size_p();

  void on_point_mode(int index);

  void on_projection_mode(int index);

  void on_reset();

  void on_save_bmp();

  void on_save_gif();

  void on_reset_affin();

  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_min_y_rot_clicked();

  void on_plus_y_rot_clicked();

  void on_min_x_rot_clicked();

  void on_plus_x_rot_clicked();

 private:
  Ui::MainWindow *ui;
  QString settingFile;
  QString fileName;
  QTimer *timer;
  QGifImage *gif;
  QImage *gifImage;
  int gifTime = 0;
  void color_by_customer();
  void connectSetup();
  void defaultSettings();
  void saveSettings();
  double current_scale = 0;
  int current_anngle_z = 0;
};
#endif  // MAINWINDOW_H

#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QColorDialog>
#include <QOpenGLWidget>
#include <QPushButton>
#include <algorithm>
#include <cstring>

using namespace std;
extern "C" {
#include "../backend/parser_and_transform/s21_3DV_v1.h"
}

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();
  QColor backgroundColor;
  QColor lineColor;
  QColor dotColor;

  int projectionMode;
  int pointMode;
  int pointSize;
  int lineSize;
  int lineMode;

  data_t data = {0, 0, NULL, 0.0, {0, 0, 0}, NULL, NULL, 0, NULL};

  char model_file_name[S_SIZE] = {0};

  void initSettings();

 public slots:
  void setScale(int scale);

 private:
  int scaleVal = 1;

  int prev_scale = 1;

  void setupPerspective();

  void pointDrawing();
  void lineDrawing();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};

#endif  // GLWIDGET_H
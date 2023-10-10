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
#include "../backend/matrix/s21_matrix.h"
#include "../backend/parcer.h"
}

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();
  QColor backgroundColor;
  QColor lineColor;
  QColor dotColor;

  int projectionMode = 0;
  int pointMode = 0;
  int pointSize = 0;
  int lineSize = 0;
  int lineMode = 0;

  main_data data = {NULL, 0, NULL, 0,   0,    0, 0, 0, 0,
                    0,    0, 0,    0.5, NULL, 0, 0, 1};

  char model_file_name[1024] = {0};

  void initSettings();

 public:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void setupPerspective();
};

#endif  // GLWIDGET_H

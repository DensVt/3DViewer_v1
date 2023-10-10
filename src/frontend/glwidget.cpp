#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) { initSettings(); }

GLWidget::~GLWidget() {}

void GLWidget::initSettings() {
  projectionMode = 0;
  pointSize = 5;
  pointMode = 0;
  lineSize = 1;
  lineMode = 0;
  backgroundColor.setRgb(0, 0, 0);
  lineColor.setRgb(255, 255, 255);
  dotColor.setRgb(255, 255, 255);
}

void GLWidget::initializeGL() {
  glClearColor(0.0, 0.0, 0.0, 1.0);  // Заливка черным цветом
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);  // Установка точки опоры
  glMatrixMode(GL_PERSPECTIVE_CORRECTION_HINT);
  glLoadIdentity();
}

void GLWidget::paintGL() {
  if (data.correct_obj == 1) {
    glClearColor(backgroundColor.redF(), backgroundColor.greenF(),
                 backgroundColor.blueF(), backgroundColor.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);  // Инициализация матрицы проекции
    glLoadIdentity();  // Сброс матрицы проекции

    setupPerspective();

    glMatrixMode(GL_MODELVIEW);  // Инициализация матрицы модели
    glLoadIdentity();  // Сброс матрицы вида модели
    for (int k = 0; k < (int)data.count_edge; k++) {
      if (pointMode != 0) {
        glColor3d(dotColor.redF(), dotColor.greenF(), dotColor.blueF());
        glPointSize(pointSize);
        for (int i = 0; i < (int)data.poligons[k].columns; i++) {
          glBegin(GL_POINTS);
          double x =
              data.arr_ver->matrix[(int)data.poligons[k].matrix[0][i]][0];
          double y =
              data.arr_ver->matrix[(int)data.poligons[k].matrix[0][i]][1];
          double z =
              data.arr_ver->matrix[(int)data.poligons[k].matrix[0][i]][2];
          glVertex3d(x, y, z);
        }
        glEnd();
      }
      if (lineMode == 1) {
        glEnable(GL_LINE_STIPPLE);
        glLineStipple(2, 0x00F0);
      } else {
        glDisable(GL_LINE_STIPPLE);
      }
      glColor3d(lineColor.redF(), lineColor.greenF(), lineColor.blueF());
      glLineWidth(lineSize);
      for (int i = 0; i < (int)data.poligons[k].columns; i++) {
        glBegin(GL_LINE_LOOP);
        double x = data.arr_ver->matrix[(int)data.poligons[k].matrix[0][i]][0];
        double y = data.arr_ver->matrix[(int)data.poligons[k].matrix[0][i]][1];
        double z = data.arr_ver->matrix[(int)data.poligons[k].matrix[0][i]][2];
        glVertex3d(x, y, z);
      }
      glEnd();
    }
  }
}

void GLWidget::setupPerspective() {
  double max_coord = max_from_axes(data.max_X, data.max_Y, data.max_Z);
  if (max_coord < 1) {
    max_coord = 2;
  }
  GLdouble zNear = 0.001;  // Ближнее расстояние отсечения
  GLdouble zFar = max_coord * 10;  // Дальнее расстояние отсечения

  if (projectionMode == 0) {  // Central/Perspective projection

    GLdouble fovY = 90;  // Поле зрения в градусах по оси y
    GLdouble fH = tan(fovY / 360 * M_PI) * zNear;
    GLdouble fW = fH;

    glFrustum(-fW, fW, -fH, fH, zNear,
              zFar);  // Устанавливает усеченный конус в режим перспективы
    glTranslatef(0, 0, -max_coord);
  } else {  // Parallel/Orthographic projection
    glOrtho(-max_coord, max_coord, -max_coord, max_coord, -max_coord, zFar);
  }
}

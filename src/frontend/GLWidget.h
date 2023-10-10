#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

extern "C" {
    #include "../backend/parser.h"
}

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = nullptr);
    void loadData(Vertex* vertices, int numVertices);

protected:
    void initializeGL() override;
    void paintGL() override;

private:
    GLuint vertexBuffer;
    Vertex* vertices;
    int numVertices;
};

#endif // GLWIDGET_H
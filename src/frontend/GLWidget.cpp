#include "GLWidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
}

void GLWidget::loadData(Vertex* vertices, int numVertices)
{
    // Здесь сохраняйте данные вершин для дальнейшего использования в paintGL
    this->vertices = vertices;
    this->numVertices = numVertices;
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    // Здесь создавайте буферы вершин и загружайте данные
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);
}

void GLWidget::paintGL()
{
    // Здесь рисуйте данные вершин
    // Атрибуты вершин
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // Отрисовка
    int num_triangles = numVertices / 3;
    for(int i = 0; i < num_triangles; ++i) {
        glDrawArrays(GL_TRIANGLES, i*3, 3);
    }

    // Освобождение ресурсов
    glDisableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Отвязка буфера
}
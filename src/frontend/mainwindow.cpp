// #include "mainwindow.h"
// #include "ui_mainwindow.h"
// #include <QFileDialog>
// #include <QDebug>
// #include <QOpenGLFunctions>

// extern "C" {
//     #include "../backend/parser.h"
// }


// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);
//     // connect(ui->open_file, &QPushButton::clicked, this, &MainWindow::on_open_file_clicked);
// }

// MainWindow::~MainWindow()
// {
//     delete ui;
// }

// void MainWindow::on_open_file_clicked()
// {
//     QString filters("OBJ files (*.obj);;All files (*.*)");
//     QString defaultFilter("OBJ files (*.obj)");

//     QString fileName = QFileDialog::getOpenFileName(this,
//                                                     tr("Open File"),
//                                                     "/home",
//                                                     filters,
//                                                     &defaultFilter);
//     if (!fileName.isEmpty())
//     {
//         qDebug() << "Выбран файл:" << fileName;
//         parse_obj_file(fileName.toStdString().c_str());

//         // Инициализация функций OpenGL
//         initializeOpenGLFunctions();

//         // Вершинный буфер
//         glGenBuffers(1, &vertexBuffer);
//         glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//         glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

//         // Атрибуты вершин
//         glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
//         glEnableVertexAttribArray(0);
//         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

//         // Отрисовка
//         int num_triangles = num_vertices / 3;
//         for(int i = 0; i < num_triangles; ++i) {
//             glDrawArrays(GL_TRIANGLES, i*3, 3);
//         }
//         glDrawArrays(GL_TRIANGLES, 0, num_vertices);

//         // Освобождение ресурсов
//         glDisableVertexAttribArray(0);
//         glBindBuffer(GL_ARRAY_BUFFER, 0); // Отвязка буфера
//         glDeleteBuffers(1, &vertexBuffer); // Удаление буфера
//     }
// }





#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "GLWidget.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QOpenGLFunctions>

extern "C" {
    #include "../backend/parser.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , glWidget(new GLWidget(this))
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout; 
    layout->addWidget(glWidget);  
    this->setCentralWidget(new QWidget);
    this->centralWidget()->setLayout(layout);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_file_clicked()
{
    QString filters("OBJ files (*.obj);;All files (*.*)");
    QString defaultFilter("OBJ files (*.obj)");

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open File"),
                                                    "/home",
                                                    filters,
                                                    &defaultFilter);
    if (!fileName.isEmpty())
    {
        qDebug() << "Выбран файл:" << fileName;
        parse_obj_file(fileName.toStdString().c_str());
        glWidget->loadData(vertices, num_vertices);
    }
}
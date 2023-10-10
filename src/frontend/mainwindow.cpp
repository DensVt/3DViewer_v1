#include "mainwindow.h"

#include "glwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  setlocale(LC_NUMERIC, "C");
  ui->setupUi(this);
  setWindowTitle("3DViewer_v1.0");

  timer = new QTimer;
  gifImage = new QImage[50]{};
  connect(timer, SIGNAL(timeout()), this, SLOT(slotTimer()));
  connect(ui->background_set, SIGNAL(clicked()), this, SLOT(on_background_color_menu()));
  connect(ui->lines_color_set, SIGNAL(clicked()), this, SLOT(on_line_color_menu()));
  connect(ui->dot_color_set, SIGNAL(clicked()), this, SLOT(on_dot_color_menu()));
  connect(ui->line_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(on_line_mode(int)));
  connect(ui->lwidth_m, SIGNAL(clicked()), this, SLOT(on_line_size_sub()));
  connect(ui->lwidth_p, SIGNAL(clicked()), this, SLOT(on_line_size_plus()));
  connect(ui->rot_x, SIGNAL(valueChanged(int)), this, SLOT(rot_x_spin(int)));
  connect(ui->rot_y, SIGNAL(valueChanged(int)), this, SLOT(rot_y_spin(int)));
  connect(ui->rot_z, SIGNAL(valueChanged(int)), this, SLOT(rot_z_spin(int)));
  connect(ui->scale_plus, SIGNAL(clicked()), this, SLOT(on_scale_plus()));
  connect(ui->scale_sub, SIGNAL(clicked()), this, SLOT(on_scale_sub()));
  connect(ui->moove_x_p, SIGNAL(clicked()), this, SLOT(on_moove_x_plus()));
  connect(ui->moove_x_sub, SIGNAL(clicked()), this, SLOT(on_moove_x_sub()));
  connect(ui->moove_y_p, SIGNAL(clicked()), this, SLOT(on_moove_y_plus()));
  connect(ui->moove_y_sub, SIGNAL(clicked()), this, SLOT(on_moove_y_sub()));
  connect(ui->dot_size_p, SIGNAL(clicked()), this, SLOT(on_point_size_p()));
  connect(ui->dot_size_sub, SIGNAL(clicked()), this, SLOT(on_point_size_s()));
  connect(ui->dot_type, SIGNAL(currentIndexChanged(int)), this, SLOT(on_point_mode(int)));
  connect(ui->projection_mode, SIGNAL(currentIndexChanged(int)), this, SLOT(on_projection_mode(int)));
  connect(ui->reset, SIGNAL(clicked()), this, SLOT(on_reset()));
  connect(ui->save_bmp, SIGNAL(clicked()), this, SLOT(on_save_bmp()));
  connect(ui->save_gif, SIGNAL(clicked()), this, SLOT(on_save_gif()));
  this->settingFile = QApplication::applicationDirPath() + "/settings.conf";

  connectSetup();
  defaultSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  remove_data(&ui->OGLWidget->data);
  delete timer;
  delete[] gifImage;
  delete ui;
}

void MainWindow::connectSetup() {
  // Open file
  connect(ui->open_button, &QRadioButton::pressed, (this), &MainWindow::on_action_triggered);
}

void MainWindow::defaultSettings() {
  if (QFile::exists(settingFile)) {
    QSettings settings(settingFile, QSettings::IniFormat);

    settings.beginGroup("LineSet");
    if (settings.value("solid").toBool()) {
      ui->OGLWidget->lineMode = 1;
    } else if (settings.value("dashed").toBool()) {
      ui->OGLWidget->lineMode = 0;
    }
    if (settings.value("LineColor").toString().length() > 0) {
      ui->OGLWidget->lineColor = settings.value("LineColor").toString();
    }
    settings.endGroup();

    settings.beginGroup("Verticies");
    if (settings.value("disable").toBool()) {
      ui->OGLWidget->pointMode = 0;

    } else if (settings.value("circle").toBool()) {
      ui->OGLWidget->pointMode = 1;

    } else if (settings.value("square").toBool()) {
      ui->OGLWidget->pointMode = 2;
    }
    ui->OGLWidget->dotColor = settings.value("color").toString();
    settings.endGroup();

    settings.beginGroup("background");
    if (settings.value("color").toString().length() > 0) {
      ui->OGLWidget->backgroundColor = settings.value("color").toString();
    }
    settings.endGroup();
  }
}

void MainWindow::saveSettings() {
  QSettings settings(settingFile, QSettings::IniFormat);

  settings.beginGroup("LineSet");
  settings.setValue("LineColor", ui->OGLWidget->lineColor);
  settings.endGroup();

  settings.beginGroup("Verticies");
  settings.setValue("color", ui->OGLWidget->dotColor);
  settings.endGroup();

  settings.beginGroup("background");
  settings.setValue("color", ui->OGLWidget->backgroundColor);
  settings.endGroup();
}

int valueNormalize(int val) {
  while (val > 180) {
    val -= 360;
  }
  while (val < -180) {
    val += 360;
  }
  return val;
}

void MainWindow::on_action_triggered() {
  QFileDialog *fileDialog = new QFileDialog(this);
  if (ui->OGLWidget->data.poligons && ui->OGLWidget->data.arr_ver){
      remove_data(&ui->OGLWidget->data);
     ui->OGLWidget->data = {NULL, 0, NULL, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0.5, NULL, 0, 0, 1};
  }
  if (fileDialog) {
    fileDialog->setWindowTitle(tr("Choose .obj-file"));
    fileDialog->setNameFilter(tr("(*.obj)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    QStringList fileNames;
    if (fileDialog->exec()) {
      fileNames = fileDialog->selectedFiles();
      if (fileNames.size() > 0) {
        QString fileName = fileNames.at(0);
        QByteArray ba = fileName.toLocal8Bit();
        char *input = ba.data();
        if (parcer(input, &ui->OGLWidget->data)){
            setWindowTitle(fileName);
            ui->statusBar->showMessage("Path: " + fileName);
            ui->number_of_facets->setText(QString::number(ui->OGLWidget->data.count_edge));
            ui->number_of_vertices->setText(QString::number(ui->OGLWidget->data.count_ver));
          }
        }
    }
    delete fileDialog;
  } else {
    printf("error!\n");
  }
  if (ui->OGLWidget->data.correct_obj == 0){
      ui->info->setText("Uncorrecct obj file!");
  }
  else{
       ui->info->setText("open obj ok!");
  }

}

void MainWindow::slotTimer() {
  if (gifTime < 50) {
    gifImage[gifTime] = ui->OGLWidget->grab().toImage();
    ++gifTime;
  } else {
    gif = new QGifImage;

    for (int i = 0; i < gifTime; ++i) {
      gif->addFrame(gifImage[i], 0);
    }
    QDateTime dateTime = dateTime.currentDateTime();
    QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss_zzz");
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save GIF", "GIF_" + currentDateTime, "GIF (*.gif)");
    gif->save(fileName);
    ui->save_gif->setEnabled(true);
    timer->stop();
    delete gif;
    gifTime = 0;
  }
}

void MainWindow::rot_z_spin(int value)
{
    value =ui->rot_z->value();
    rot_z(&ui->OGLWidget->data, value);
    ui->OGLWidget->update();
}

void MainWindow::rot_y_spin(int value)
{
    value = ui->rot_y->value();
    rot_y(&ui->OGLWidget->data, value);
    ui->OGLWidget->update();
}

void MainWindow::rot_x_spin(int value)
{
    value = ui->rot_x->value();
    rot_x(&ui->OGLWidget->data, value);
    ui->OGLWidget->update();
}

void MainWindow::on_moove_y_plus()
{
    double delta_y = 0.1;
    moove(&ui->OGLWidget->data,0, delta_y);
    ui->OGLWidget->update();
}

void MainWindow::on_moove_y_sub()
{
    double delta_y = -0.1;
    moove(&ui->OGLWidget->data,0, delta_y);
    ui->OGLWidget->update();
}

void MainWindow::on_moove_x_sub()
{
    double delta_x = -0.1;
    moove(&ui->OGLWidget->data, delta_x, 0);
    ui->OGLWidget->update();
}

void MainWindow::on_moove_x_plus()
{
    double delta_x = 0.1;
    moove(&ui->OGLWidget->data, delta_x, 0);
    ui->OGLWidget->update();
}

void MainWindow::on_scale_plus()
{
    double scale_val = 1.1;
    if (scale_val != 0){
        scale(scale_val, &ui->OGLWidget->data);
        ui->OGLWidget->update();
    }
}

void MainWindow::on_scale_sub()
{
    double scale_val = 0.9;
    if (scale_val != 0){
        scale(scale_val, &ui->OGLWidget->data);
        ui->OGLWidget->update();
    }
}

void MainWindow::on_background_color_menu() {
  QColor color = QColorDialog::getColor();
  if (color.isValid()) {
    ui->OGLWidget->backgroundColor = color;
    ui->OGLWidget->update();
  }
}

void MainWindow::on_line_color_menu()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
      ui->OGLWidget->lineColor = color;
      ui->OGLWidget->update();
    }
}

void MainWindow::on_dot_color_menu()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
      ui->OGLWidget->dotColor = color;
      ui->OGLWidget->update();
    }
}

void MainWindow::on_line_size_plus()
{
    ui->OGLWidget->lineSize += 1;
    ui->OGLWidget->update();

}

void MainWindow::on_line_size_sub()
{
        ui->OGLWidget->lineSize -= 1;
        ui->OGLWidget->update();

}

void MainWindow::on_line_mode(int index)
{
    index = ui->line_mode->currentIndex();
    if (index == 1) ui->OGLWidget->lineMode = 1;
    else ui->OGLWidget->lineMode = 0;
    ui->OGLWidget->update();
}

void MainWindow::on_point_size_s()
{
    ui->OGLWidget->pointSize += 1;
    ui->OGLWidget->update();

}

void MainWindow::on_point_size_p()
{
    ui->OGLWidget->pointSize -= 1;
    ui->OGLWidget->update();

}

void MainWindow::on_point_mode(int index)
{
    index = ui->dot_type->currentIndex();
    ui->OGLWidget->pointMode = index;
    ui->OGLWidget->update();
}

void MainWindow::on_projection_mode(int index)
{
    index = ui->projection_mode->currentIndex();
    ui->OGLWidget->projectionMode = index;
     ui->OGLWidget->update();
}

void MainWindow::on_reset()
{
    ui->OGLWidget->backgroundColor.setRgb(0, 0, 0);
    ui->OGLWidget->lineColor.setRgb(255, 255, 255);
    ui->OGLWidget->dotColor.setRgb(255, 255, 255);
    ui->OGLWidget->projectionMode = 0;
    ui->OGLWidget->pointSize = 5;
    ui->OGLWidget->pointMode = 0;
    ui->OGLWidget->lineSize = 1;
    ui->OGLWidget->lineMode = 0;
    ui->OGLWidget->update();
}

void MainWindow::on_save_bmp()
{
    QFileDialog dialogPhoto(this);
    QDateTime dateTime = dateTime.currentDateTime();
    QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss_zzz");
    QString name_photo = dialogPhoto.getSaveFileName(
        this, "Save as...", "Screenshot_" + currentDateTime,
        "BMP (*.bmp);; JPEG (*.jpeg)");
    ui->OGLWidget->grabFramebuffer().save(name_photo);
}

void MainWindow::on_save_gif()
{
    ui->save_gif->setEnabled(false);
    timer->start(100);
}


#include "main_window.h"

#include <external/gif.h>

#include <iostream>
#include <stdexcept>

#include "./ui_main_window.h"
#include "QFileDialog"
#include "QtCore/qstring.h"
#include "QtWidgets/qwidget.h"
#include "view/i_render_view.h"
#include "view/ui/settings_window.h"

s21::MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  QSurfaceFormat window_surface = QSurfaceFormat::defaultFormat();
  window_surface.setMajorVersion(3);
  window_surface.setMinorVersion(3);
  window_surface.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(window_surface);

  state_.scale.setX(1);
  state_.scale.setY(1);
  state_.scale.setZ(1);
  state_.rotation.setX(0);
  state_.rotation.setY(0);
  state_.rotation.setZ(0);
  state_.position.setX(0);
  state_.position.setY(0);
  state_.position.setZ(0);

  ui->setupUi(this);

  settings_ = new QSettings();
  settings_window = new SettingsWindow{nullptr, ui->openGLWidget, settings_};

  connect(this, &MainWindow::closing, settings_window, &SettingsWindow::close);

  setWindowTitle("3DViewer_v2.0");
}
s21::MainWindow::~MainWindow() {
  delete ui;
  delete settings_window;
}

void s21::MainWindow::SubscribeLoad(LoadDelegate delegate) {
  on_load_ = delegate;
}
void s21::MainWindow::SubscribeTransform(TransformDelegate delegate) {
  on_transform_ = delegate;
}
void s21::MainWindow::SubscribeDelete(DeleteDelegate delegate) {
  on_delete_ = delegate;
}

namespace s21 {
void MainWindow::on_actionOpen_triggered() {
  QString file_name = QFileDialog::getOpenFileName(
      this, "Open a file", QDir::homePath(), "OBJ Files (*.obj)");
  file_path = file_name.toStdString();
  settings_window->LoadSettings(settings_);
  if (!file_path.empty()) {
    on_load_(file_path, *(ui->openGLWidget));
    SetUIValuesToDefault();
    SetStatusBarInfo();
  }
}
void MainWindow::SetStatusBarInfo() {
  int vertex_count = ui->openGLWidget->grabbed()->vertexCount();
  int edge_count = ui->openGLWidget->grabbed()->indexCount();
  QString info = "vertices: " + QString::number(vertex_count) +
                 "\tedges: " + QString::number(edge_count);
  ui->statusBar->showMessage(info);
}

void MainWindow::on_doubleSpinBox_position_X_valueChanged(double arg1) {
  try {
    state_.position.setX(arg1);
    on_transform_(state_, *(ui->openGLWidget));
    ui->openGLWidget->update();
  } catch (const std::out_of_range& oor) {
  }
}

void MainWindow::on_doubleSpinBox_position_Y_valueChanged(double arg1) {
  try {
    state_.position.setY(arg1);
    on_transform_(state_, *(ui->openGLWidget));
    ui->openGLWidget->update();
  } catch (const std::out_of_range& oor) {
  }
}

void MainWindow::on_doubleSpinBox_position_Z_valueChanged(double arg1) {
  try {
    state_.position.setZ(arg1);
    on_transform_(state_, *(ui->openGLWidget));
    ui->openGLWidget->update();
  } catch (std::out_of_range& oor) {
  }
}

void MainWindow::on_doubleSpinBox_rotation_X_valueChanged(double arg1) {
  try {
    state_.rotation.setX(arg1);
    on_transform_(state_, *(ui->openGLWidget));
    ui->openGLWidget->update();
  } catch (std::out_of_range& oor) {
  }
}

void MainWindow::on_doubleSpinBox_rotation_Y_valueChanged(double arg1) {
  try {
    state_.rotation.setY(arg1);
    on_transform_(state_, *(ui->openGLWidget));
    ui->openGLWidget->update();
  } catch (std::out_of_range& oor) {
  }
}

void MainWindow::on_doubleSpinBox_rotation_Z_valueChanged(double arg1) {
  try {
    state_.rotation.setZ(arg1);
    on_transform_(state_, *(ui->openGLWidget));
    ui->openGLWidget->update();
  } catch (std::out_of_range& oor) {
  }
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1) {
  try {
    state_.scale.setX(arg1);
    state_.scale.setY(arg1);
    state_.scale.setZ(arg1);
    on_transform_(state_, *(ui->openGLWidget));
    ui->openGLWidget->update();
  } catch (std::out_of_range& oor) {
  }
}

void MainWindow::on_actionViewport_Settings_triggered() {
  settings_window->show();
}

void MainWindow::on_pushButton_make_cube_released() {
  on_load_("cube", *(ui->openGLWidget));
  settings_window->LoadSettings(settings_);
  ui->openGLWidget->update();
  SetStatusBarInfo();
  SetUIValuesToDefault();
}

void MainWindow::on_pushButton_delete_object_released() {
  on_delete_();
  ui->openGLWidget->clear();
  ui->openGLWidget->update();
  ui->statusBar->showMessage("");
  SetUIValuesToDefault();
}
void MainWindow::SetUIValuesToDefault() {
  ui->doubleSpinBox_scale->setValue(1);
  ui->doubleSpinBox_position_X->setValue(0);
  ui->doubleSpinBox_position_Y->setValue(0);
  ui->doubleSpinBox_position_Z->setValue(0);
  ui->doubleSpinBox_rotation_X->setValue(0);
  ui->doubleSpinBox_rotation_Y->setValue(0);
  ui->doubleSpinBox_rotation_Z->setValue(0);
}
void MainWindow::on_pushButton_record_released() {
  if (record_) {
    ui->pushButton_record->setStyleSheet("background-color: grey");
    QString fileName = QFileDialog::getSaveFileName(
        0, "Сохранить как...", QDir::currentPath(), "GIF (*.gif)");
    if (!fileName.isNull()) {
      if (!fileName.endsWith(".gif")) fileName.append(".gif");
      GifWriter gif;
      if (frames_.size()) {
        auto frame = frames_.begin();
        GifBegin(&gif, fileName.toStdString().c_str(), frame->width(),
                 frame->height(), 10);
        for (; frame != frames_.end(); frame++) {
          GifWriteFrame(&gif,
                        frame->convertToFormat(QImage::Format_Indexed8)
                            .convertToFormat(QImage::Format_RGBA8888)
                            .constBits(),
                        frame->width(), frame->height(), 10);
        }
        GifEnd(&gif);
      }
      frames_.clear();
    }
  }
  record_ = !record_;
  if (record_ == true)
    ui->pushButton_record->setStyleSheet("background-color: red");
  frame_ = 0;
}

void MainWindow::paintEvent(QPaintEvent* event) {
  QMainWindow::paintEvent(event);
  if (record_) {
    if (!(frame_ % 10)) {
      frames_.push_back(ui->openGLWidget->getFrame());
    }
    ++frame_;
  }
}

void MainWindow::on_actionExport_bmp_triggered() {
  QString fileName = QFileDialog::getSaveFileName(
      0, "Сохранить как...", QDir::currentPath(), "BMP (*.bmp)");
  if (!fileName.isNull()) {
    if (!fileName.endsWith(".bmp")) fileName.append(".bmp");
    ui->openGLWidget->grabFramebuffer().save(fileName, "BMP", 100);
  }
}

void MainWindow::on_actionExport_jpeg_triggered() {
  QString fileName = QFileDialog::getSaveFileName(
      0, "Сохранить как...", QDir::currentPath(), "JPG (*.jpeg *.jpg)");
  if (!fileName.isNull()) {
    if (!fileName.endsWith(".jpeg") || !fileName.endsWith(".jpg"))
      fileName.append(".jpeg");
    ui->openGLWidget->grabFramebuffer().save(fileName, "JPEG", 100);
  }
}

void MainWindow::closeEvent(QCloseEvent* event) {
  emit closing();
  event->accept();
}
}  // namespace s21

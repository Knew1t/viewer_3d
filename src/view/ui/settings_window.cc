#include "settings_window.h"

#include "./ui_settings_window.h"
#include "QtCore/qlogging.h"
#include "QtCore/qsettings.h"
#include "QtWidgets/qlayout.h"
#include "main_window.h"
#include "view/render/renderer.h"

s21::SettingsWindow::SettingsWindow(QWidget *parent, Renderer *ren_ptr,
                                    QSettings *inc_settings)
    : QWidget(parent),
      ui_(new Ui::SettingsWindow),
      settings(inc_settings),
      renderer(ren_ptr) {
  ui_->setupUi(this);
  setWindowTitle("Settings");
  setFixedSize(QSize(640, 864));

  color_dialog_ = new QColorDialog;
  color_dialog_->setWindowFlags(Qt::Widget);
  color_dialog_->setStyleSheet(
      "background-color: rgb(246, 245, 244);"
      "font: bold;"
      "color: rgb(94, 92, 100);");
  color_dialog_->setOptions(QColorDialog::DontUseNativeDialog |
                            QColorDialog::NoButtons);
  ui_->frame_bg_color->layout()->addWidget(color_dialog_);

  background_color_ = new QColor;
  background_color_->setRgbF(0.39, 0.39, 0.39, 1.0);
  edge_color_ = new QColor;
  vertex_color_ = new QColor;
  projection_type_ = Renderer::ProjectionType::kPerspective;
  SetVertexBoxState();
}

s21::SettingsWindow::~SettingsWindow() {
  delete color_dialog_;
  delete settings;
  delete ui_;
  delete background_color_;
  delete edge_color_;
  delete vertex_color_;
}

void s21::SettingsWindow::on_checkBox_display_vertex_clicked_or_not_clicked() {
  SetVertexBoxState();
}

void s21::SettingsWindow::SetVertexBoxState() {
  if (ui_->checkBox_display_vertex_clicked_or_not->isChecked()) {
    ui_->checkBox_display_vertex_clicked_or_not->setStyleSheet(
        "border: 0px solid grey;"
        "color: rgb(36, 31, 49);"
        "background-color: rgb(237, 236, 232);"
        "font: bold;");
    ui_->radioButton_vertex_square->setStyleSheet(
        "border:0px solid grey;"
        "color: rgb(154, 153, 150);"
        "background-color: rgb(246, 245, 244);");
    ui_->radioButton_vertex_circle->setStyleSheet(
        "border:0px solid grey;"
        "color: rgb(154, 153, 150);"
        "background-color: rgb(246, 245, 244);");
    ui_->doubleSpinBox_vertex_size->setStyleSheet("color: rgb(154, 153, 150);");
    ui_->pushButton_vertex_color->setStyleSheet("color: rgb(154, 153, 150);");
    ui_->groupBox_vertex_options->setDisabled(true);
  } else {
    ui_->checkBox_display_vertex_clicked_or_not->setStyleSheet(
        "border: 0px solid grey;"
        "color: rgb(94, 92, 100);"
        "background-color: rgb(237, 236, 232);"
        "font: regular;");
    ui_->radioButton_vertex_square->setStyleSheet(
        "border:0px solid grey;"
        "color: rgb(0, 0, 0);"
        "background-color: rgb(246, 245, 244);");
    ui_->radioButton_vertex_circle->setStyleSheet(
        "border:0px solid grey;"
        "color: rgb(0, 0, 0);"
        "background-color: rgb(246, 245, 244);");
    ui_->doubleSpinBox_vertex_size->setStyleSheet("color: rgb(0, 0, 0);");
    ui_->pushButton_vertex_color->setStyleSheet("color: rgb(94, 92, 100);");
    ui_->groupBox_vertex_options->setEnabled(true);
  }
}

namespace s21 {
void SettingsWindow::on_pushButton_apply_settings_released() {
  *background_color_ = color_dialog_->currentColor();
  if (ui_->radioButton_edge_solid->isChecked()) {
    edge_type_ = Renderer::EdgeType::kSolid;
  } else {
    edge_type_ = Renderer::EdgeType::kDashed;
  }
  if (!ui_->checkBox_display_vertex_clicked_or_not->isChecked()) {
    if (ui_->radioButton_vertex_square->isChecked()) {
      vertex_type_ = Renderer::VertexType::kSquare;
    } else {
      vertex_type_ = Renderer::VertexType::kRound;
    }
    vertex_size_ = ui_->doubleSpinBox_vertex_size->value();
  } else {
    vertex_type_ = Renderer::VertexType::kDisabled;
  }
  if (ui_->radioButton_central->isChecked())
    projection_type_ = Renderer::ProjectionType::kPerspective;
  else
    projection_type_ = Renderer::ProjectionType::kOrthographic;
  edge_thickness_ = ui_->doubleSpinBox_edge_width->value();
  ApplySettings();
}

void SettingsWindow::on_pushButton_save_settings_released() {
  settings->setValue("background color red", background_color_->redF());
  settings->setValue("background color green", background_color_->greenF());
  settings->setValue("background color blue", background_color_->blueF());

  settings->setValue("edge_type", (int)edge_type_);

  settings->setValue("edge_color red", edge_color_->redF());
  settings->setValue("edge_color green", edge_color_->greenF());
  settings->setValue("edge_color blue", edge_color_->blueF());

  settings->setValue("vertex_color red", vertex_color_->redF());
  settings->setValue("vertex_color green", vertex_color_->greenF());
  settings->setValue("vertex_color blue", vertex_color_->blueF());

  settings->setValue("edge_thickness", ui_->doubleSpinBox_edge_width->value());
  settings->setValue("vertex_type", (int)vertex_type_);
  settings->setValue("vertex_size", ui_->doubleSpinBox_vertex_size->value());

  settings->setValue("projection_type", (int)projection_type_);
}

void SettingsWindow::on_pushButton_edge_color_released() {
  QColorDialog color_dialog;
  *edge_color_ = color_dialog.getColor();
}

void SettingsWindow::on_pushButton_vertex_color_released() {
  QColorDialog color_dialog;
  *vertex_color_ = color_dialog.getColor();
}

void SettingsWindow::LoadSettings(QSettings *inc_settings) {
  settings = inc_settings;
  settings->contains("background color red");
  background_color_->setRedF(
      settings->value("background color red", 0.4).toFloat());
  background_color_->setGreenF(
      settings->value("background color green", 0.4).toFloat());
  background_color_->setBlueF(
      settings->value("background color blue", 0.4).toFloat());
  color_dialog_->setCurrentColor(*background_color_);

  edge_type_ = (Renderer::EdgeType)settings->value("edge_type", 0).toInt();
  if (edge_type_ == Renderer::EdgeType::kSolid)
    ui_->radioButton_edge_solid->setChecked(true);
  else {
    ui_->radioButton_edge_dashed->setChecked(true);
  }

  vertex_type_ =
      (Renderer::VertexType)settings->value("vertex_type", 0).toInt();

  if (vertex_type_ != Renderer::VertexType::kDisabled) {
    ui_->checkBox_display_vertex_clicked_or_not->setChecked(false);
    SetVertexBoxState();
    ui_->doubleSpinBox_vertex_size->setValue(vertex_size_);
    if (vertex_type_ == Renderer::VertexType::kRound)
      ui_->radioButton_vertex_circle->setChecked(true);
    else
      ui_->radioButton_vertex_circle->setChecked(false);
  }

  vertex_size_ = settings->value("vertex_size", 1).toDouble();

  edge_color_->setRedF(settings->value("edge_color red", 0).toFloat());
  edge_color_->setGreenF(settings->value("edge_color green", 0).toFloat());
  edge_color_->setBlueF(settings->value("edge_color blue", 0).toFloat());

  vertex_color_->setRedF(settings->value("vertex_color red", 0).toFloat());
  vertex_color_->setGreenF(settings->value("vertex_color green", 0).toFloat());
  vertex_color_->setBlueF(settings->value("vertex_color blue", 0).toFloat());

  projection_type_ =
      (Renderer::ProjectionType)settings->value("projection_type", 0).toInt();
  qDebug() << (int)projection_type_;
  if (projection_type_ == Renderer::ProjectionType::kPerspective) {
    ui_->radioButton_central->setChecked(true);
  } else {
    ui_->radioButton_parallel->setChecked(true);
  }

  edge_thickness_ = settings->value("edge_thickness", 1).toDouble();
  ui_->doubleSpinBox_edge_width->setValue(edge_thickness_);
  ApplySettings();
}

void SettingsWindow::ApplySettings() {
  renderer->backgroundColor(*background_color_);
  renderer->edgeType(edge_type_);
  renderer->vertexColor(*vertex_color_);
  renderer->edgeColor(*edge_color_);
  renderer->vertexType(vertex_type_);
  renderer->edgeThickness(edge_thickness_);
  renderer->setProjection(projection_type_);
  renderer->vertexSize(vertex_size_);
}

void SettingsWindow::on_horizontalSlider_edge_width_valueChanged(int value) {
  ui_->doubleSpinBox_edge_width->setValue(value);
}

void SettingsWindow::on_horizontalSlider_vertex_size_valueChanged(int value) {
  ui_->doubleSpinBox_vertex_size->setValue(value);
}

void SettingsWindow::on_doubleSpinBox_edge_width_valueChanged(double arg1) {
  ui_->horizontalSlider_edge_width->setValue(arg1);
}

void SettingsWindow::on_doubleSpinBox_vertex_size_valueChanged(double arg1) {
  ui_->horizontalSlider_vertex_size->setValue(arg1);
}

}  // namespace s21

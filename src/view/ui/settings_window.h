#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <QColorDialog>
#include <QMainWindow>
#include <QSettings>

#include "../render/renderer.h"
#include "QtCore/qsettings.h"
#include "QtGui/qmatrix4x4.h"

namespace Ui {
class SettingsWindow;
}

namespace s21 {
class MainWindow;  // this is here to avoid recursion during preprocessor stage
class SettingsWindow : public QWidget {
  Q_OBJECT
 public:
  explicit SettingsWindow(QWidget *parent = nullptr, Renderer *ptr = nullptr,
                          QSettings *settings = nullptr);
  ~SettingsWindow();
  void LoadSettings(QSettings *);
  void ApplySettings();

 private slots:
  void on_checkBox_display_vertex_clicked_or_not_clicked();

  void on_pushButton_apply_settings_released();

  void on_pushButton_save_settings_released();

  void on_pushButton_edge_color_released();

  void on_pushButton_vertex_color_released();

  void on_horizontalSlider_edge_width_valueChanged(int value);

  void on_horizontalSlider_vertex_size_valueChanged(int value);

  void on_doubleSpinBox_edge_width_valueChanged(double arg1);

  void on_doubleSpinBox_vertex_size_valueChanged(double arg1);

 private:
  void SetVertexBoxState();
  Ui::SettingsWindow *ui_;
  QColorDialog *color_dialog_;
  QSettings *settings;
  QColor *background_color_;
  QColor *edge_color_;
  QColor *vertex_color_;
  Renderer::ProjectionType projection_type_;
  Renderer::EdgeType edge_type_;
  Renderer::VertexType vertex_type_;
  double vertex_size_;
  double edge_thickness_;
  Renderer *renderer;
};
}  // namespace s21

#endif  // SETTINGS_WINDOW_H

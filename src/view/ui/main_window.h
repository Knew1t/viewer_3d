#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCloseEvent>
#include <QMainWindow>
#include <vector>

#include "../i_render_view.h"
#include "QtWidgets/qwidget.h"
#include "settings_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
namespace s21 {
class MainWindow : public QMainWindow, public s21::IRenderView {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void SubscribeLoad(LoadDelegate) override;
  void SubscribeTransform(TransformDelegate) override;
  void SubscribeDelete(DeleteDelegate) override;

 protected:
  void paintEvent(QPaintEvent *event) override;
  void closeEvent(QCloseEvent *event) override;
 signals:
  void closing();

 private slots:

  void on_doubleSpinBox_position_X_valueChanged(double arg1);

  void on_doubleSpinBox_position_Y_valueChanged(double arg1);

  void on_doubleSpinBox_position_Z_valueChanged(double arg1);

  void on_actionOpen_triggered();

  void on_doubleSpinBox_rotation_X_valueChanged(double arg1);

  void on_doubleSpinBox_rotation_Y_valueChanged(double arg1);

  void on_doubleSpinBox_rotation_Z_valueChanged(double arg1);

  void on_doubleSpinBox_scale_valueChanged(double arg1);

  void on_actionViewport_Settings_triggered();
  void on_pushButton_make_cube_released();

  void on_pushButton_delete_object_released();

  void on_pushButton_record_released();

  void on_actionExport_bmp_triggered();

  void on_actionExport_jpeg_triggered();

 private:
  void SetUIValuesToDefault();
  void SetStatusBarInfo();
  IRenderView::LoadDelegate on_load_;
  IRenderView::TransformDelegate on_transform_;
  IRenderView::DeleteDelegate on_delete_;
  std::string file_path;  // TEMPORARY
  Ui::MainWindow *ui;
  SettingsWindow *settings_window;
  QSettings *settings_;
  Transform state_;
  bool record_ = false;
  uint32_t frame_;
  QList<QImage> frames_;
};
};      // namespace s21
#endif  // MAINWINDOW_H

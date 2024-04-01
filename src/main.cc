#include <view/ui/main_window.h>

#include <QApplication>

#include "controller/application_controller.h"
#include "model/scene.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MainWindow view;
  s21::Scene model;
  s21::ApplicationController w{&model, &view};
  view.show();
  return a.exec();
}

#include "view.h"

#include <QApplication>

int main(int argc, char *argv[]) {

  QApplication a(argc, argv);

  s21::Snake *snake;
  snake = new s21::Snake;
  s21::Controller *controller = new s21::Controller(snake);
  s21::View view(controller);
  view.show();

  return a.exec();
}

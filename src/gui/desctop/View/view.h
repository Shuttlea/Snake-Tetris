#ifndef VIEW_H
#define VIEW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <iostream>

#include "../../../brick_game/tetris/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class View;
}
QT_END_NAMESPACE

namespace s21 {

class View : public QMainWindow {
  Q_OBJECT

public:
  void keyPressEvent(QKeyEvent *event) override;
  View(Controller *controller, QWidget *parent = nullptr);
  ~View();

protected:
  void paintEvent(QPaintEvent *event) override;

private slots:
  void slotTimerAlarm();
  void on_snakeButton_clicked();
  void on_tetrisButton__clicked();

private:
  GameInfo_t gmInf_;
  QTimer *tmr_;
  Controller *controller_;
  Ui::View *ui;
  QColor coloring(int value);
  void restartGame(s21::Model &model);

signals:
  void signal();
};

} // namespace s21
#endif // VIEW_H

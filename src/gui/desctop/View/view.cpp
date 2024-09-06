#include "view.h"
#include "./ui_view.h"

namespace s21 {

void View::keyPressEvent(QKeyEvent *event) {
  UserAction_t signal = Empty;
  switch (event->key()) {
  case 16777220:
    ui->label_6->hide();
    signal = Start;
    break;
  case Qt::Key_P:
    signal = Pause;
    break;
  case Qt::Key_Escape:
    close();
    break;
  case Qt::Key_Left:
    signal = Left;
    break;
  case Qt::Key_Right:
    signal = Right;
    break;
  case Qt::Key_Up:
    signal = Up;
    break;
  case Qt::Key_Down:
    signal = Down;
    break;
  case Qt::Key_Space:
    signal = Action;
    break;
  }
  controller_->userInput(signal);
  update();
}

View::View(Controller *controller, QWidget *parent)
    : controller_(controller), QMainWindow(parent), ui(new Ui::View) {
  ui->setupUi(this);
  tmr_ = new QTimer();
  connect(tmr_, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
  tmr_->start(340);
}

View::~View() { delete ui; }

void View::paintEvent(QPaintEvent *event) {
  gmInf_ = controller_->updateCurrentState();
  ui->score->setText(QString::number(gmInf_.score));
  ui->high_score->setText(QString::number(gmInf_.high_score));
  ui->level->setText(QString::number(gmInf_.level));

  if (ui->speed->text().toDouble() < gmInf_.speed) {
    tmr_->start(360 - 20 * gmInf_.speed);
    ui->speed->setText(QString::number(gmInf_.speed));
  }

  QPainter p(this);
  p.setPen(QColor(Qt::green));
  p.setBrush(QBrush(Qt::black, Qt::SolidPattern));
  p.drawRect(19, 19, 202, 402);
  for (int i = 0; i < 20; ++i)
    for (int j = 0; j < 10; ++j)
      if (gmInf_.field[i][j]) {
        p.setPen(coloring(gmInf_.field[i][j]));
        p.setBrush(QBrush(coloring(gmInf_.field[i][j]), Qt::SolidPattern));
        p.drawRect(20 + 20 * j, 20 + 20 * i, 20, 20);
      }
  if (gmInf_.next != NULL)
    for (int i = 0; i < 5; ++i)
      for (int j = 0; j < 5; ++j)
        if (gmInf_.next[i * 5 + j]) {
          p.setPen(coloring(gmInf_.next[i * 5 + j]));
          p.setBrush(
              QBrush(coloring(gmInf_.next[i * 5 + j]), Qt::SolidPattern));
          p.drawRect(220 + 20 * j, 160 + 20 * i, 20, 20);
        }
  View::update();
}

void View::slotTimerAlarm() {
  if (controller_->getState() != PAUSE)
    controller_->shifting();
  update();
}

QColor View::coloring(int value) {
  QColor color;
  switch (value) {
  case 22:
    color = Qt::green;
    break;
  case 1:
    color = Qt::red;
    break;
  case 202:
    color = Qt::white;
    break;
  case 3:
    color = Qt::blue;
    break;
  case 219:
    color = Qt::cyan;
    break;
  case 20:
    color = Qt::magenta;
    break;
  case 90:
    color = Qt::yellow;
  }
  return color;
}

void View::on_snakeButton_clicked() {
  s21::Snake *snake = new s21::Snake;
  restartGame(*snake);
  ui->label_6->show();
}

void View::on_tetrisButton__clicked() {
  s21::Tetris *tetris = new s21::Tetris;
  restartGame(*tetris);
  ui->label_6->show();
}

void View::restartGame(s21::Model &model) {
  tmr_->stop();
  delete controller_;
  controller_ = new s21::Controller(&model);
  gmInf_ = controller_->updateCurrentState();
  ui->speed->setText(QString::number(gmInf_.speed));
  tmr_->start(340);
}

} // namespace s21

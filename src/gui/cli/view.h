#ifndef VIEW_H
#define VIEW_H

#include <ncurses.h>
#include <stdio.h>
#include <time.h>

#include "../../brick_game/tetris/controller.h"

namespace s21 {

class View {
private:
  Controller *controller_;
  clock_t speed_ = 20000;

public:
  View(Controller *c) : controller_(c){};
  void startEventLoop();

private:
  void print_action(GameInfo_t gmInf);
  void print_overlay();
  void print_rectangle(int top_y, int bottom_y, int left_x, int right_x);
  void print_pixel(int x, int y, int color);
  void print_figure(int x, int y, int *shape);
  UserAction_t get_signal(int user_input);
};

} // namespace s21

#endif
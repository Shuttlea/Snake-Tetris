#include "view.h"

namespace s21 {

void View::startEventLoop() {
  clock_t clock1 = clock();
  clock_t clock2;
  GameInfo_t gmInf;
  // clock_t speed = 20000;
  // print_overlay();
  const State_t &state = controller_->getState();

  while (state != EXIT && state != GAME_OVER) {
    controller_->userInput(get_signal(getch()));
    clock2 = clock();
    if (state == MOVING && clock2 - clock1 >= speed_) {
      clock1 = clock2;
      controller_->shifting();
    }
    gmInf = controller_->updateCurrentState();
    speed_ = 20000 - (clock_t)gmInf.speed * 1000;
    print_action(gmInf);
  }
}

void View::print_action(GameInfo_t gmInf) {
  clear();
  for (int i = 0; i < 20; ++i)
    for (int j = 0; j < 10; ++j)
      if (gmInf.field[i][j])
        print_pixel(j, i, gmInf.field[i][j]);
  mvprintw(3, 40, "%d", gmInf.score);
  mvprintw(7, 40, "%d", gmInf.high_score);
  mvprintw(11, 40, "%d", gmInf.level);
  mvprintw(15, 40, "%d", gmInf.speed);
  if (gmInf.next != NULL)
    print_figure(17, 13, gmInf.next);
  print_overlay();
  refresh();
}

void View::print_overlay() {
  print_rectangle(0, 41, 0, 31);
  print_rectangle(0, 41, 33, 55);
  print_rectangle(1, 4, 34, 54);
  print_rectangle(5, 8, 34, 54);
  print_rectangle(9, 12, 34, 54);
  print_rectangle(13, 16, 34, 54);
  print_rectangle(17, 27, 34, 54);
  mvprintw(2, 38, "SCORE:");
  mvprintw(6, 38, "HIGH SCORE:");
  mvprintw(10, 38, "LEVEL:");
  mvprintw(14, 38, "SPEED:");
  mvprintw(18, 38, "NEXT FIGURE:");
}

void View::print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
  mvaddch(top_y, left_x, ACS_ULCORNER);

  int i = left_x + 1;

  for (; i < right_x; i++)
    mvaddch(top_y, i, ACS_HLINE);
  mvaddch(top_y, i, ACS_URCORNER);

  for (int i = top_y + 1; i < bottom_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  mvaddch(bottom_y, left_x, ACS_LLCORNER);
  i = left_x + 1;
  for (; i < right_x; i++)
    mvaddch(bottom_y, i, ACS_HLINE);
  mvaddch(bottom_y, i, ACS_LRCORNER);
}

void View::print_figure(int x, int y, int *shape) {
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j) {
      if (shape[i * 5 + j])
        print_pixel(x - 5 + j, y - 5 + i, shape[i * 5 + j]);
    }
}

void View::print_pixel(int x, int y, int color) {
  start_color();
  init_pair(color, COLOR_BLACK, color);
  attron(COLOR_PAIR(color));
  mvprintw(y * 2 + 1, x * 3 + 1, "   ");
  mvprintw(y * 2 + 2, x * 3 + 1, "   ");
  attroff(COLOR_PAIR(color));
}

UserAction_t View::get_signal(int user_input) {
  UserAction_t rc = Empty;
  if (user_input == 259)
    rc = Up;
  else if (user_input == 258)
    rc = Down;
  else if (user_input == 260)
    rc = Left;
  else if (user_input == 261)
    rc = Right;
  else if (user_input == 27)
    rc = Terminate;
  else if (user_input == 10)
    rc = Start;
  else if (user_input == 32)
    rc = Action;
  else if (user_input == 112)
    rc = Pause;
  return rc;
}

} // namespace s21
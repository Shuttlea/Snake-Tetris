#include <iostream>

#include "view.h"

s21::Model *menu();

int main() {
  s21::Model *model = menu();
  if (model != NULL) {
    s21::Controller controller(model);
    s21::View view(&controller);
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(40);
    srand(time(NULL));
    view.startEventLoop();
    endwin();
  }
  return 0;
}

s21::Model *menu() {
  int k;
  s21::Model *model = NULL;
  std::cout << "Choose the game:\n 1. Tetris\n 2. Snake\n";
  std::cin >> k;
  if (k == 1) {
    static s21::Tetris tetris;
    model = &tetris;
  } else if (k == 2) {
    static s21::Snake snake;
    model = &snake;
  }

  return model;
}

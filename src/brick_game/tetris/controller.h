#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../snake/snake.h"
#include "tetris.h"

namespace s21 {

class Controller {
private:
  Model *model_;

public:
  Controller(Model *m) : model_(m) {}
  void userInput(UserAction_t action);
  GameInfo_t updateCurrentState();
  void shifting();
  const State_t &getState();
};

} // namespace s21

#endif

#include "controller.h"

namespace s21 {

void Controller::userInput(UserAction_t action) {
  model_->userInput(action, 1);
}

GameInfo_t Controller::updateCurrentState() {
  return model_->updateCurrentState();
}

void Controller::shifting() { model_->shifting(); }

const State_t &Controller::getState() { return model_->getState(); }

} // namespace s21
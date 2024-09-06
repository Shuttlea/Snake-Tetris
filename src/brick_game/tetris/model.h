#ifndef MODEL_H
#define MODEL_H

#include "declarations.h"

namespace s21 {

class Model {
public:
  virtual void userInput(UserAction_t action, bool hold) = 0;
  virtual GameInfo_t updateCurrentState() = 0;
  virtual void shifting() = 0;
  virtual const State_t &getState() const = 0;
};

} // namespace s21

#endif
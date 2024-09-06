#ifndef SNAKE_H
#define SNAKE_H

/*!
\file
\brief Файл содержит описание класса Snake
*/

#include <ctime>
#include <fstream>
#include <list>
#include <stdlib.h>

#include "../tetris/model.h"
#include "declarations.h"

namespace s21 {

class Snake : public Model {
private:
  GameInfo_t gmInf_;
  State_t state_ = START;
  UserAction_t action_ = Empty;
  UserAction_t move_ = Up;
  UserAction_t prevMove_ = Up;
  std::list<std::pair<int, int>> snake_;
  std::pair<int, int> apple_;
  void stateMachine();
  void spawn();
  bool moveSnake();
  void put_apple();
  bool checkCollisions(int x, int y);
  void eatingApple();

public:
  Snake();
  ~Snake() {}
  void userInput(UserAction_t action,
                 bool hold = 1) override; ///< Принимает действие пользователя
  GameInfo_t
  updateCurrentState() override; ///< Возвращает текущее состояние игры
  void shifting()
      override; ///< Изменяет состояние игры по истечении игрового таймера
  const State_t &getState() const
      override; ///< Возвращает состояние конечного автомата на данный момент
};

} // namespace s21

#endif
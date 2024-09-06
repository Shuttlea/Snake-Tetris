#ifndef TETRIS_H
#define TETRIS_H

#include <fstream>
#include <stdlib.h>

#include "allShapes.h"
#include "declarations.h"
#include "model.h"

namespace s21 {

typedef struct {
  int x; ///< горизонтальная координата центра фигуры
  int y; ///< вертикальная координата центра фигуры
  int *shape; ///< фигура, которой управляет игрок в данный момент
} User_t;

class Tetris : public Model {
private:
  GameInfo_t gmInf_;
  State_t state_ = START;
  UserAction_t action_ = Empty;
  User_t user_;
  int allShapes_[700] = ALL_SHAPES;

public:
  Tetris();
  ~Tetris();
  void userInput(UserAction_t action, bool hold = 1) override;
  GameInfo_t updateCurrentState() override;
  void shifting() override;
  const State_t &getState() const override;

private:
  void stateMachine();
  void spawn();
  void includePlayerToField();
  void erasePlayerFromField();
  bool moveBottom();
  bool moveRight();
  bool moveLeft();
  void rotateShape();
  void scoring(int &score);
  bool attaching();
};

} // namespace s21

#endif
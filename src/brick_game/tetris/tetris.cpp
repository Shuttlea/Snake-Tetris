#include "tetris.h"

namespace s21 {

Tetris::Tetris() {
  for (int i = 0; i < 20; ++i)
    for (int j = 0; j < 10; ++j)
      gmInf_.field[i][j] = 0;
  srand(time(NULL));
  rand();
  gmInf_.next = allShapes_ + rand() % 7 * 100;
  gmInf_.score = 0;
  gmInf_.level = 1;
  gmInf_.speed = 1;
  gmInf_.pause = 1;
  std::ifstream ifs("tetrisHighScore", std::ios::binary);
  if (ifs.is_open()) {
    ifs >> gmInf_.high_score;
    ifs.close();
  } else {
    std::ofstream ofs("tetrisHighScore", std::ios::binary);
    gmInf_.high_score = 0;
    ofs << gmInf_.high_score;
    ofs.close();
  }
}

Tetris::~Tetris() {}

void Tetris::userInput(UserAction_t action, bool hold) {
  if (hold)
    action_ = action;
  stateMachine();
}

GameInfo_t Tetris::updateCurrentState() { return gmInf_; }

void Tetris::shifting() {
  if (state_ == MOVING)
    state_ = SHIFTING;
  stateMachine();
}

const State_t &Tetris::getState() const { return state_; }

void Tetris::stateMachine() {
  switch (state_) {
  case START:
    switch (action_) {
    case Start:
      state_ = SPAWN;
      break;
    case Terminate:
      state_ = EXIT;
      break;
    default:
      break;
    }
    break;

  case SPAWN:
    spawn();
    state_ = MOVING;
    break;

  case SHIFTING:
    if (!moveBottom())
      state_ = ATTACHING;
    else
      state_ = MOVING;
    break;

  case MOVING:
    switch (action_) {
    case Terminate:
      state_ = EXIT;
      break;
    case Right:
      moveRight();
      break;
    case Left:
      moveLeft();
      break;
    case Down:
      if (!moveBottom())
        state_ = ATTACHING;
      break;
    case Up:
      rotateShape();
      break;
    case Action:
      while (moveBottom())
        ;
      break;
    case Pause:
      gmInf_.pause = 1;
      state_ = PAUSE;
      break;
    default:
      break;
    }
    break;

  case ATTACHING:
    if (attaching())
      state_ = SPAWN;
    else
      state_ = GAME_OVER;
    break;

  case PAUSE:
    if (action_ == Pause) {
      gmInf_.pause = 0;
      state_ = MOVING;
    }
    break;

  case GAME_OVER:
    break;

  default:
    break;
  }
}

void Tetris::spawn() {
  user_.x = 4;
  user_.y = 0;
  user_.shape = gmInf_.next;
  gmInf_.next = allShapes_ + rand() % 7 * 100;
  includePlayerToField();
}

void Tetris::includePlayerToField() {
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      if (user_.y - 2 + i >= 0 && user_.shape[i * 5 + j] != 0)
        gmInf_.field[user_.y - 2 + i][user_.x - 2 + j] = user_.shape[i * 5 + j];
}

void Tetris::erasePlayerFromField() {
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      if (user_.y - 2 + i >= 0 && user_.shape[i * 5 + j] != 0)
        gmInf_.field[user_.y - 2 + i][user_.x - 2 + j] = 0;
}

bool Tetris::moveBottom() {
  erasePlayerFromField();
  bool res = 1;
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      if (user_.shape[i * 5 + j] != 0 &&
          (gmInf_.field[user_.y - 1 + i][user_.x - 2 + j] != 0 ||
           user_.y - 1 + i > 19))
        res = 0;
  if (res)
    ++user_.y;
  includePlayerToField();
  return res;
}

bool Tetris::moveRight() {
  erasePlayerFromField();
  bool res = 1;
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      if (user_.shape[i * 5 + j] != 0 &&
          (gmInf_.field[user_.y - 2 + i][user_.x - 1 + j] != 0 ||
           user_.x - 1 + j > 9))
        res = 0;
  if (res)
    ++user_.x;
  includePlayerToField();
  return res;
}

bool Tetris::moveLeft() {
  erasePlayerFromField();
  bool res = 1;
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j)
      if (user_.shape[i * 5 + j] != 0 &&
          (gmInf_.field[user_.y - 2 + i][user_.x - 3 + j] != 0 ||
           user_.x - 3 + j < 0))
        res = 0;
  if (res)
    --user_.x;
  includePlayerToField();
  return res;
}

void Tetris::rotateShape() {
  erasePlayerFromField();
  int *check;
  bool ch = 1;
  check = ((user_.shape + 25 - allShapes_) % 100) ? user_.shape + 25
                                                  : user_.shape - 75;
  for (int i = 0; i < 5; ++i)
    for (int j = 0; j < 5; ++j) {
      if (check[i * 5 + j] != 0 &&
          (user_.x - 2 + j < 0 || user_.x - 2 + j > 9 ||
           gmInf_.field[user_.y - 2 + i][user_.x - 2 + j] != 0))
        ch = 0;
    }
  if (ch)
    user_.shape = check;
  includePlayerToField();
}

void Tetris::scoring(int &score) {
  switch (score) {
  case 1:
    gmInf_.score += 100;
    break;
  case 2:
    gmInf_.score += 300;
    break;
  case 3:
    gmInf_.score += 700;
    break;
  default:
    gmInf_.score += 1500;
    break;
  }
}

bool Tetris::attaching() {
  int count, j, score = 0;
  bool res = 1;
  for (int i = 19; i >= 0; --i) {
    count = 0;
    for (j = 0; j < 10; ++j)
      if (gmInf_.field[i][j])
        ++count;
      else
        break;
    if (count == 10) {
      ++score;
      for (int z = i; z > 0; --z)
        for (j = 0; j < 10; ++j)
          gmInf_.field[z][j] = gmInf_.field[z - 1][j];
      for (j = 0; j < 10; ++j)
        gmInf_.field[0][j] = 0;
      ++i;
    }
  }
  if (score)
    scoring(score);
  if (gmInf_.score > gmInf_.high_score) {
    gmInf_.high_score = gmInf_.score;
    std::ofstream ofs("tetrisHighScore", std::ios::binary);
    ofs << gmInf_.high_score;
    ofs.close();
  }
  gmInf_.level = (gmInf_.score / 600 + 1 <= 10) ? gmInf_.score / 600 + 1 : 10;
  gmInf_.speed = gmInf_.level;
  for (j = 0; j < 10; ++j)
    if (gmInf_.field[0][j])
      res = 0;
  return res;
}

} // namespace s21

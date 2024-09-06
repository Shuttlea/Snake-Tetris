#include "snake.h"

namespace s21 {

void Snake::stateMachine() {
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
    if (moveSnake())
      state_ = MOVING;
    else
      state_ = EXIT;
    break;

  case MOVING:
    switch (action_) {
    case Terminate:
      state_ = EXIT;
      break;
    case Up:
      if (prevMove_ != Down)
        move_ = Up;
      break;
    case Right:
      if (prevMove_ != Left)
        move_ = Right;
      break;
    case Down:
      if (prevMove_ != Up)
        move_ = Down;
      break;
    case Left:
      if (prevMove_ != Right)
        move_ = Left;
      break;
    case Action:
      shifting();
      break;
    case Pause:
      gmInf_.pause = 1;
      state_ = PAUSE;
      break;
    default:
      break;
    }
    break;

  case PAUSE:
    if (action_ == Pause) {
      gmInf_.pause = 0;
      state_ = MOVING;
    }
    break;

  default:
    break;
  }
}

void Snake::spawn() {
  snake_.push_front({4, 13});
  snake_.push_front({4, 12});
  snake_.push_front({4, 11});
  snake_.push_front({4, 10});
  gmInf_.field[13][4] = 22;
  gmInf_.field[12][4] = 22;
  gmInf_.field[11][4] = 22;
  gmInf_.field[10][4] = 22;
  put_apple();
}

bool Snake::moveSnake() {
  bool res = true;
  int x = snake_.front().first;
  int y = snake_.front().second;
  switch (move_) {
  case Up:
    --y;
    break;
  case Right:
    ++x;
    break;
  case Down:
    ++y;
    break;
  case Left:
    --x;
    break;
  default:
    break;
  }
  if (!checkCollisions(x, y))
    res = false;
  else {
    prevMove_ = move_;
    snake_.push_front({x, y});
    gmInf_.field[y][x] = 22;
    if (x == apple_.first && y == apple_.second)
      eatingApple();
    else {
      gmInf_.field[snake_.back().second][snake_.back().first] = 0;
      snake_.pop_back();
    }
  }
  return res;
}

void Snake::eatingApple() {
  ++gmInf_.score;
  if (gmInf_.score > gmInf_.high_score) {
    gmInf_.high_score = gmInf_.score;
    std::ofstream ofs("snakeHighScore", std::ios::binary);
    ofs << gmInf_.high_score;
    ofs.close();
  }
  if (!(gmInf_.score % 5) && gmInf_.level < 10) {
    ++gmInf_.level;
    ++gmInf_.speed;
  }
  if (gmInf_.score < 196)
    put_apple();
  else
    state_ = EXIT;
}

void Snake::put_apple() {
  std::srand(time(0));
  int n = (std::rand() % (199 - snake_.size()));
  for (int i = 0; i <= n; ++i) {
    if (gmInf_.field[i / 10][i % 10])
      ++n;
  }
  apple_.first = n % 10;
  apple_.second = n / 10;
  gmInf_.field[apple_.second][apple_.first] = 1;
}

bool Snake::checkCollisions(int x, int y) {
  bool res = 1;
  if (x < 0 || x > 9 || y < 0 || y > 19)
    res = false;
  for (auto it : snake_)
    if (x == it.first && y == it.second)
      res = false;
  return res;
}

Snake::Snake() {
  for (int i = 0; i < 20; ++i)
    for (int j = 0; j < 10; ++j)
      gmInf_.field[i][j] = 0;
  gmInf_.next = NULL;
  gmInf_.score = 0;
  gmInf_.level = 1;
  gmInf_.speed = 1;
  gmInf_.pause = 1;
  std::ifstream ifs("snakeHighScore", std::ios::binary);
  if (ifs.is_open()) {
    ifs >> gmInf_.high_score;
    ifs.close();
  } else {
    std::ofstream ofs("snakeHighScore", std::ios::binary);
    gmInf_.high_score = 0;
    ofs << gmInf_.high_score;
    ofs.close();
  }
}

// Snake::~Snake() {}

void Snake::userInput(UserAction_t action, bool hold) {
  if (hold)
    action_ = action;
  stateMachine();
}

GameInfo_t Snake::updateCurrentState() { return gmInf_; }

void Snake::shifting() {
  if (state_ == MOVING) {
    state_ = SHIFTING;
  }
  stateMachine();
}

const State_t &Snake::getState() const { return state_; }

} // namespace s21

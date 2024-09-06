#include "googletest.h"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(SnakeTest, stateMachine_START_Test1) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  ASSERT_TRUE(snakeT.getState() == s21::SPAWN);
}

TEST(SnakeTest, stateMachine_START_Test2) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Terminate, 1);
  ASSERT_TRUE(snakeT.getState() == s21::EXIT);
}

TEST(SnakeTest, stateMachine_START_Test3) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Left, 1);
  ASSERT_TRUE(snakeT.getState() == s21::START);
}

TEST(SnakeTest, stateMachine_SPAWN_Test) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  ASSERT_TRUE(snakeT.getState() == s21::MOVING);
}

TEST(SnakeTest, stateMachine_SPAWN_Test2) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.shifting();
  snakeT.shifting();
  ASSERT_TRUE(snakeT.getState() == s21::MOVING);
}

TEST(SnakeTest, stateMachine_MOVING_Test1) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Terminate, 1);
  ASSERT_TRUE(snakeT.getState() == s21::EXIT);
}

TEST(SnakeTest, stateMachine_MOVING_Test2) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Up, 1);
  snakeT.shifting();
  ASSERT_TRUE(snakeT.updateCurrentState().field[9][4] == 22);
  ASSERT_TRUE(snakeT.updateCurrentState().field[13][4] == 0);
}

TEST(SnakeTest, stateMachine_MOVING_Test3) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Down, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Up, 1);
  ASSERT_TRUE(snakeT.updateCurrentState().field[9][4] == 22);
  ASSERT_TRUE(snakeT.updateCurrentState().field[13][4] == 0);
}

TEST(SnakeTest, stateMachine_MOVING_Test4) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Right, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Down, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Up, 1);
  ASSERT_TRUE(snakeT.updateCurrentState().field[10][5] == 22);
  ASSERT_TRUE(snakeT.updateCurrentState().field[13][4] == 0);
}

TEST(SnakeTest, stateMachine_MOVING_Test5) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Left, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Right, 1);
  ASSERT_TRUE(snakeT.updateCurrentState().field[10][3] == 22);
  ASSERT_TRUE(snakeT.updateCurrentState().field[13][4] == 0);
}

TEST(SnakeTest, stateMachine_MOVING_Test6) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Action, 1);
  snakeT.shifting();
  ASSERT_TRUE(snakeT.updateCurrentState().field[8][4] == 22);
  ASSERT_TRUE(snakeT.updateCurrentState().field[13][4] == 0);
}

TEST(SnakeTest, stateMachine_MOVING_Test7) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Pause, 1);
  ASSERT_TRUE(snakeT.getState() == s21::PAUSE);
  ASSERT_TRUE(snakeT.updateCurrentState().pause == 1);
}

TEST(SnakeTest, stateMachine_MOVING_Test8) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Empty, 1);
  snakeT.shifting();
  ASSERT_TRUE(snakeT.updateCurrentState().field[9][4] == 22);
  ASSERT_TRUE(snakeT.updateCurrentState().field[13][4] == 0);
}

TEST(SnakeTest, stateMachine_MOVING_Test9) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Right, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Left, 1);
  ASSERT_TRUE(snakeT.updateCurrentState().field[10][5] == 22);
  ASSERT_TRUE(snakeT.updateCurrentState().field[13][4] == 0);
}

TEST(SnakeTest, stateMachine_MOVING_Test10) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Pause, 1);
  snakeT.userInput(s21::Pause, 1);
  ASSERT_TRUE(snakeT.getState() == s21::MOVING);
  ASSERT_TRUE(snakeT.updateCurrentState().pause == 0);
}

TEST(SnakeTest, stateMachine_MOVING_Test11) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Pause, 1);
  snakeT.userInput(s21::Empty, 1);
  ASSERT_TRUE(snakeT.getState() == s21::PAUSE);
  ASSERT_TRUE(snakeT.updateCurrentState().pause == 1);
}

TEST(SnakeTest, stateMachine_EATING_YOURSELF_Test) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Right, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Down, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Left, 1);
  snakeT.shifting();
  ASSERT_TRUE(snakeT.getState() == s21::EXIT);
}

TEST(SnakeTest, stateMachine_CHECK_COLLISIONS_Test1) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Up, 1);
  for (int i = 0; i < 20; ++i)
    snakeT.shifting();
  ASSERT_TRUE(snakeT.getState() == s21::EXIT);
}

TEST(SnakeTest, stateMachine_CHECK_COLLISIONS_Test2) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Right, 1);
  for (int i = 0; i < 20; ++i)
    snakeT.shifting();
  ASSERT_TRUE(snakeT.getState() == s21::EXIT);
}

TEST(SnakeTest, stateMachine_CHECK_COLLISIONS_Test3) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Left, 1);
  for (int i = 0; i < 20; ++i)
    snakeT.shifting();
  ASSERT_TRUE(snakeT.getState() == s21::EXIT);
}

TEST(SnakeTest, stateMachine_CHECK_COLLISIONS_Test4) {
  s21::Snake snakeT;
  snakeT.userInput(s21::Start, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Left, 1);
  snakeT.shifting();
  snakeT.userInput(s21::Down, 1);
  for (int i = 0; i < 20; ++i)
    snakeT.shifting();
  ASSERT_TRUE(snakeT.getState() == s21::EXIT);
}

#ifndef DECLARATIONS_H
#define DECLARATIONS_H

namespace s21 {

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  Empty
} UserAction_t;

typedef struct {
  int field[20][10];
  int *next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  START = 0, ///< Стартовое состояние
  SPAWN,     ///< Образование новой фигуры
  MOVING, ///< Состояние движения от действий пользователя
  SHIFTING,  ///< Состояние движения по таймеру
  GAME_OVER, ///< Конец игры
  EXIT,      ///< Выход
  PAUSE,     ///< Пауза
  ATTACHING ///< Подсчет и уничтожение заполненных строк, подсчет очков и
            ///< рекордов в тетрисе
} State_t;

} // namespace s21

#endif
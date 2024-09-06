#ifndef DECLARATIONS_H
#define DECLARATIONS_H

/*!
\file
\brief Файл содержит описание структур и перечислений (enum) в игре
*/

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
  int field[20][10]; ///< Игровое поле
  int *next; ///<  Следующая фигура (используется в игре тетрис, в змейке имеет
             ///<  значение NULL)
  int score; ///< Текущее количество очков
  int high_score; ///< Рекордное количество очков
  int level;      ///< Текущий уровень
  int speed;      ///< Текущая скорость
  int pause;      ///< Состояние паузы
} GameInfo_t; ///< Структура, в которой хранятся все данные для вывода на экран

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
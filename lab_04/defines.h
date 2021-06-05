#ifndef DIRECTION_H
#define DIRECTION_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <vector>

#define STAY_TIME 2000
#define CLOSING_TIME 2000
#define OPENING_TIME 2000
#define MOVEMENT_TIME 2000

#define START_FLOOR 1
#define START_TARGET 0

#define FLOORS_AMOUNT 8

enum direction
{
    UP = 1,
    DOWN = -1,
    STAY = 0
};

#endif // DIRECTION_H

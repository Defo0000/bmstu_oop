#ifndef DEFINES_H
#define DEFINES_H

#include <QObject>
#include <QDebug>
#include <QTimer>

#define FLOORS_AMOUNT 8
#define START_STATE -1
#define START_FLOOR 1

#define FLOOR_PASSING_TIME 1500
#define DOORS_ACTIVITY_TIME 2000
#define ELEVATOR_WAITING_TIME 2000

template <typename T>
using vector = std::vector<T>;

enum direction
{
    DOWN = -1,
    STAY = 0,
    UP = 1
};

#endif // DEFINES_H

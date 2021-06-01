#ifndef DEFINES_H
#define DEFINES_H

#include <QObject>
#include <QDebug>

#define FLOORS_AMOUNT 8
#define START_STATE -1
#define START_FLOOR 1

template <typename T>
using vector = std::vector<T>;

enum direction
{
    DOWN = -1,
    STAY = 0,
    UP = 1
};

#endif // DEFINES_H

#include "controller.h"
#include <stdio.h>

controller::controller(QObject *parent): QObject(parent)
{
    is_target.resize(FLOORS_AMOUNT);
    for (int i = 0; i < FLOORS_AMOUNT; i++)
        is_target[i] = false;

    QObject::connect(this, SIGNAL(controller_new_target(int, direction)), this, SLOT(busy(int, direction)));
}

void controller::new_target(int floor)
{
    qDebug() << "В лифте был вызван" << floor << "этаж.\n";
    is_target[floor - 1] = true;
    if (state == FREE)
    {
        next_target();
    }
}

void controller::busy(int floor, const direction &dir)
{
    if (state == FREE)
    {
        state = BUSY;

        cur_target = floor;
        cur_direction = dir;
    }
    else if (state == BUSY)
    {
        qDebug() << "Лифт проезжает" << floor << "этаж.\n";

        cur_floor += cur_direction;
    }
}

void controller::free(int floor)
{
    state = FREE;

    cur_floor = floor;

    next_target();
}

void controller::next_target()
{
    if (is_target[cur_floor - 1])
    {
        is_target[cur_floor - 1] = false;
        emit controller_new_target(cur_floor, STAY);
    }
    else
    {
        for (int i = 0; i < FLOORS_AMOUNT; i++)
        {
            if (is_target[i])
            {
                is_target[i] = false;

                if (i + 1 > cur_floor)
                    emit controller_new_target(i + 1, UP);
                else
                    emit controller_new_target(i + 1, DOWN);
            }
        }
    }
}

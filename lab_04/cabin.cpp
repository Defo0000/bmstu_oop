#include "cabin.h"
#include <stdio.h>

cabin::cabin(QObject *parent): QObject(parent)
{
    movement_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(cabin_called()), this, SLOT(move()));
    QObject::connect(this, SIGNAL(cabin_stopped()), &_doors, SLOT(opening()));
    QObject::connect(this, SIGNAL(cabin_target_reached(int)), this, SLOT(stop(int)));
    QObject::connect(&_doors, SIGNAL(doors_closed()), this, SLOT(wait()));
    QObject::connect(&movement_timer, SIGNAL(timeout()), this, SLOT(move()));
}

void cabin::stop(int floor)
{
    if (state != MOVE)
        return;

    state = STOP;

    qDebug() << "Кабина остановилась на"<< floor << "этаже.\n";

    emit cabin_stopped();
}

void cabin::wait()
{
    if (state != STOP)
        return;

    state = WAIT;

    qDebug() << "Ожидание пассажиров.\n";

    emit cabin_wait(cur_floor);
}

void cabin::move()
{
    if (state != START_MOVE && state != MOVE)
        return;

    if (state == MOVE)
    {
        cur_floor += cur_direction;
    }

    state = MOVE;

    if (cur_floor == cur_target)
    {
        emit cabin_target_reached(cur_floor);
    }
    else
    {
        emit cabin_passed_floor(cur_floor, cur_direction);

        movement_timer.start(MOVEMENT_TIME);
    }
}

void cabin::get_target(int floor, const direction &dir)
{
    if (state != WAIT)
        return;

    state = START_MOVE;

    cur_target = floor;
    cur_direction = dir;

    emit cabin_called();
}

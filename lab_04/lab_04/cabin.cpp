#include "cabin.h"

cabin::cabin(QObject *parent) : QObject(parent), cur_floor(START_FLOOR), target(START_STATE),
    new_target(false), cur_state(cabin::STAND), cur_direction(STAY)
{
    passing_floor_timer.setSingleShot(true);

    QObject::connect(this, SIGNAL(cabin_called()), &_doors, SLOT(start_closing()));
    QObject::connect(this, SIGNAL(cabin_reached_target(int)), this, SLOT(cabin_stopping()));
    QObject::connect(this, SIGNAL(cabin_stopped(int)), &_doors, SLOT(start_openning()));
    QObject::connect(&_doors, SIGNAL(closed_doors()), this, SLOT(cabin_move()));
    QObject::connect(&passing_floor_timer, SIGNAL(timeout()), this, SLOT(cabin_move()));
}

void cabin::cabin_move()
{

    if (new_target)
    {
        if (cur_state == WAIT)
        {
            cur_state = MOVE;

            if (cur_floor == target)
            {
                emit cabin_reached_target(cur_floor);
            }
            else
            {
                passing_floor_timer.start(FLOOR_PASSING_TIME);
            }
        }
        else if (cur_state == MOVE)
        {
            cur_floor += cur_direction;

            if (cur_floor == target)
            {
                emit cabin_reached_target(cur_floor);
            }
            else
            {
                emit cabin_passing_floor(cur_floor);
                passing_floor_timer.start(FLOOR_PASSING_TIME);
            }
        }
    }
}

void cabin::cabin_stopping()
{
    if (cur_state == MOVE)
    {
        cur_state = STAND;
        qDebug() << "Лифт остановился на " << cur_floor << " этаже.";
        emit cabin_stopped(cur_floor);
    }
}

void cabin::cabin_call(int floor)
{
    if (cur_state == STAND)
    {
        cur_state = WAIT;
        new_target = true;
        target = floor;

        cur_direction = STAY;
        if (cur_floor < target)
        {
            cur_direction = UP;
        }
        if (cur_floor > target)
        {
            cur_direction = DOWN;
        }

        emit cabin_stopped(cur_floor);
    }
}

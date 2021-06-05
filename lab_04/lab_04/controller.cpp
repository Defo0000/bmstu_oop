#include "controller.h"

controller::controller(QObject *parent) : 
    QObject(parent), cur_floor(START_FLOOR), cur_target(START_STATE),
    is_target(FLOORS_AMOUNT, false), cur_state(controller::FREE), cur_direction(STAY) {}

void controller::set_new_target(int floor)
{
    cur_state = controller::BUSY;
    is_target[floor - 1] = true;

    if (cur_target == START_STATE)
    {
        cur_target = floor;
    }
    if ((cur_direction == UP && floor > cur_target) ||
        (cur_direction == DOWN && floor < cur_target))
    {
        cur_target = floor; 
    }

    //next_target(floor);

    cur_floor > cur_target ? cur_direction = DOWN : cur_direction = UP;

    emit set_target(floor);
}

void controller::achieved_floor(int floor)
{
    if (cur_state == BUSY)
    {
        cur_floor = floor;
        is_target[floor - 1] = false;

        if (cur_floor == cur_target)
        {
            cur_target = START_STATE;
            find_new_target();
        }

        if (next_target(floor))
        {
            cur_floor > cur_target ? cur_direction = DOWN : cur_direction = UP;
            emit set_target(floor);
        }
        else
        {
            cur_state = FREE;
        }
    }
}

void controller::passed_floor(int floor)
{
    cur_floor = floor;
    qDebug() << "Лифт проезжает " << floor << " этаж.\n";
}

void controller::find_new_target()
{
    bool flag = false;

    if (cur_direction == UP)
    {
        for (int i = FLOORS_AMOUNT; i >= 1 && !flag; i--)
        {
            if (is_target[i - 1])
            {
                flag = true;
                cur_target = i;
            }
        }
    }
    else
    {
        for (int i = 1; i <= FLOORS_AMOUNT && !flag; i++)
        {
            if (is_target[i - 1])
            {
                flag = true;
                cur_target = i;
            }
        }
    }
}

bool controller::next_target(int &floor)
{
    bool flag = false;

    if (cur_target > cur_floor)
    {
        for (int i = cur_floor; i <= FLOORS_AMOUNT && !flag; i += 1)
        {
            if (is_target[i - 1])
            {
                floor = i;
                flag = true;
            }
        }
    }
    else
    {
        for (int i = cur_floor; i >= 1 && !flag; i -= 1)
        {
            if (is_target[i - 1])
            {
                floor = i;
                flag = true;
            }
        }
    }

    return flag;
}

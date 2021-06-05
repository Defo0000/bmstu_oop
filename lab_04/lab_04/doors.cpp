#include "defines.h"
#include "doors.h"

doors::doors(QObject *parent) : QObject(parent), cur_state(doors::CLOSED)
{
    doors_open_timer.setSingleShot(true);
    QObject::connect(&doors_open_timer, SIGNAL(timeout()), this, SLOT(open()));

    doors_close_timer.setSingleShot(true);
    QObject::connect(&doors_close_timer, SIGNAL(timeout()), this, SLOT(close()));

    doors_stay_opened_timer.setInterval(ELEVATOR_WAITING_TIME);
    doors_stay_opened_timer.setSingleShot(true);
    QObject::connect(this, SIGNAL(opened_doors()), &doors_stay_opened_timer,
                   SLOT(start()));
    QObject::connect(&doors_stay_opened_timer, SIGNAL(timeout()), this,
                   SLOT(start_closing()));
}

void doors::start_opening()
{
    if (cur_state == CLOSED)
    {
        cur_state = OPENING;

        qDebug() << "Двери открываются.\n";

        doors_open_timer.start(DOORS_ACTIVITY_TIME);
    }

    else if (cur_state == CLOSING)
    {
        cur_state = OPENING;

        qDebug() << "Двери открываются.\n";

        int remaining_time = doors_close_timer.remainingTime();
        doors_close_timer.stop();
        doors_open_timer.start(DOORS_ACTIVITY_TIME - remaining_time);
    }
}

void doors::start_closing()
{
    if (cur_state == CLOSED)
    {
        emit closed_doors();
    }

    else if (cur_state == OPENED)
    {
        cur_state = CLOSING;

        qDebug() << "Двери закрываются.\n";

        doors_close_timer.start(DOORS_ACTIVITY_TIME);
    }
}

void doors::open()
{
    if (cur_state == OPENING)
    {
        cur_state = OPENED;
        qDebug() << "Двери открыты.\n";
        emit opened_doors();
    }
}

void doors::close()
{
    if (cur_state == CLOSING)
    {
        cur_state = CLOSED;
        qDebug() << "Двери закрыты.\n";
        emit closed_doors();
    }
}

#include "doors.h"
#include <stdio.h>

doors::doors(QObject *parent): QObject(parent)
{
    stay_timer.setInterval(STAY_TIME);

    stay_timer.setSingleShot(true);
    closing_timer.setSingleShot(true);
    opening_timer.setSingleShot(true);

    QObject::connect(&closing_timer, SIGNAL(timeout()), this, SLOT(closed()));
    QObject::connect(&opening_timer, SIGNAL(timeout()), this, SLOT(opened()));
    QObject::connect(&stay_timer, SIGNAL(timeout()), this, SLOT(closing()));

    QObject::connect(this, SIGNAL(doors_opened()), &stay_timer, SLOT(start()));
}

void doors::closing()
{
    if (state != OPENED)
        return;

    qDebug() << "Двери закрываются.\n";

    state = CLOSING;
    closing_timer.start(CLOSING_TIME);
}

void doors::opening()
{
    if (state != CLOSED && state != CLOSING)
        return;

    qDebug() << "Двери открываются.\n";

    if (state == CLOSED)
    {
        state = OPENING;
        opening_timer.start(OPENING_TIME);
    }
    else if (state == CLOSING)
    {
        state = OPENING;
        int t = closing_timer.remainingTime();
        closing_timer.stop();
        opening_timer.start(OPENING_TIME - t);
    }
}

void doors::closed()
{
    if (state != CLOSING)
        return;

    qDebug() << "Двери закрылись.\n";

    state = CLOSED;

    emit doors_closed();
}

void doors::opened()
{
    if (state != OPENING)
        return;

    qDebug() << "Двери открылись.\n";
    state = OPENED;

    emit doors_opened();
}

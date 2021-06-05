#ifndef CABIN_H
#define CABIN_H

#include "doors.h"
#include "defines.h"

class cabin: public QObject
{
    Q_OBJECT

    enum cabin_state
    {
        STOP,
        WAIT,
        START_MOVE,
        MOVE
    };

public:
    explicit cabin(QObject *parent = nullptr);

signals:
    void cabin_called();
    void cabin_stopped();
    void cabin_target_reached(int floor);
    void cabin_passed_floor(int floor, const direction &dir);
    void cabin_wait(int floor);

public slots:
    void stop(int floor);
    void wait();
    void get_target(int floor, const direction &dir);
    void move();

private:
    doors _doors;
    direction cur_direction = STAY;
    cabin_state state = WAIT;
    int cur_floor = START_FLOOR;
    int cur_target = START_TARGET;

    QTimer movement_timer;
};

#endif // CABIN_H

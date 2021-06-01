#ifndef CABIN_H
#define CABIN_H

#include "defines.h"
#include "doors.h"

class cabin : public QObject
{
    Q_OBJECT

    enum cabin_state
    {
        MOVE,
        WAIT,
        STAND
    };

public:
    explicit cabin(QObject *parent = nullptr);

signals:
    void cabin_called();
    void cabin_passing_floor(int floor);
    void cabin_reached_target(int floor);
    void cabin_stopped(int floor);

public slots:
    void cabin_move();
    void cabin_stopping();
    void cabin_call(int floor);

private:
    doors _doors;
    int cur_floor;
    int cur_target;
    bool new_target;
    cabin_state cur_state;
    direction cur_direction;
    QTimer passing_floor_timer;
};

#endif // CABIN_H

#ifndef CABIN_H
#define CABIN_H

#include "defines.h"
#include "door.h"

class cabin : public QObject
{
    Q_OBJECT

    enum cabin_state
    {
        MOVE,
        ACTIVE,
        STAND
    };

public:
    explicit cabin(QObject *parent = nullptr);

signals:
    void passing_floor(int floor);
    void stop();

public slots:
    void move();
    void stand();
    void call(int floor);

private:
    door _door;
    int _floor;
    int _target;
    cabin_state _state;
    direction _direction;
};

#endif // CABIN_H

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "defines.h"

class controller: public QObject
{
    Q_OBJECT

    enum controller_state
    {
        FREE,
        BUSY
    };

public:
    explicit controller(QObject *parent = nullptr);
    void new_target(int floor);

public slots:
    void free(int floor);
    void busy(int floor, const direction &dir);

signals:
    void controller_new_target(int floor, const direction &dir);

private:
    direction cur_direction = STAY;
    int cur_floor = START_FLOOR;
    int cur_target = START_TARGET;
    controller_state state = FREE;

    void next_target();

    std::vector<bool> is_target;
};

#endif // CONTROLLER_H

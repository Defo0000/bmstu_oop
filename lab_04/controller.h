#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "defines.h"

class controller : public QObject
{
    Q_OBJECT

    enum controller_state
    {
        FREE,
        BUSY
    };

public:
    explicit controller(QObject *parent = nullptr);
    void set_new_target(int floor);

signals:
    void set_target(int floor);

public slots:
    void achieved_floor(int floor);
    void passed_floor(int floor);

private:
    vector<bool> is_target;
    
    int cur_floor;
    int cur_target;
    controller_state cur_state;
    direction cur_direction;

    bool next_target(int &floor);
    void find_new_target();
};

#endif // CONTROLLER_H

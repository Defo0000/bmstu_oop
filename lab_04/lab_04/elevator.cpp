#include "elevator.h"

elevator::elevator()
{
    QObject::connect(&_controller, SIGNAL(set_target(int)), &_cabin, SLOT(cabin_call(int)));
    QObject::connect(&_cabin, SIGNAL(cabin_passing_floor(int)), &_controller, SLOT(passed_floor(int)));
    QObject::connect(&_cabin, SIGNAL(cabin_stopped(int)), &_controller, SLOT(achieved_floor(int)));
}

void elevator::click(int floor)
{
    _controller.set_new_target(floor);
}

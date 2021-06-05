#include "elevator.h"

elevator::elevator(QObject *parent): QObject(parent)
{
    QObject::connect(&_cabin, SIGNAL(cabin_wait(int)), &_controller, SLOT(free(int)));
    QObject::connect(&_cabin, SIGNAL(cabin_passed_floor(int, direction)), &_controller, SLOT(busy(int, direction)));
    QObject::connect(&_controller, SIGNAL(controller_new_target(int, direction)), &_cabin, SLOT(get_target(int, direction)));
}

void elevator::button_pressed(int floor)
{
    _controller.new_target(floor);
}

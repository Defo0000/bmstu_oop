#ifndef ELEVATOR_H
#define ELEVATOR_H

#include "defines.h"
#include "controller.h"
#include "cabin.h"

class elevator : public QObject
{
    Q_OBJECT
    
public:
    elevator();
    void call(int floor);

private:
    controller _controller;
    cabin _cabin;
};

#endif // ELEVATOR_H

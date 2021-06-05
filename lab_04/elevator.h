#ifndef LIFT_H
#define LIFT_H

#include "defines.h"
#include "cabin.h"
#include "controller.h"

class elevator: public QObject
{
    Q_OBJECT

public:
    explicit elevator(QObject *parent = nullptr);

public slots:
    void button_pressed(int floor);

private:
    cabin _cabin;
    controller _controller;
};

#endif // LIFT_H

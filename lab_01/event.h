#ifndef EVENT_H
#define EVENT_H

#include "link.h"
#include "point.h"
#include "rc.h"

typedef const char * filename_t;

typedef enum
{
    LOAD,
    SCALE,
    MOVE,
    ROTATE,
    DRAW,
    QUIT,
} task_t;

typedef struct
{
    task_t task;
    union
    {
        filename_t filename;
        scale_t scale;
        move_t move;
        rotate_t rotate;
        plane_t plane;
    };
} event_t;

rc_t event_handler(const event_t event);

#endif // EVENT_H

#include "event.h"

rc_t event_handler(const event_t event)
{
    rc_t return_code = OK;

    switch (event.task)
    {
        case LOAD:
            
            break;
        case SCALE:
            break;
        case ROTATE:
            break;
        case MOVE:
            break;
        case DRAW:
            break;
        case QUIT:
            break;
        default:
            return_code = ERR_UNKNOWN_CMD;
    }
    return return_code;
}

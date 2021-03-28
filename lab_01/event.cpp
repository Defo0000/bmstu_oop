#include "event.h"
#include "figure.h"

rc_t event_handler(const event_t event)
{
    rc_t return_code = OK;
    figure_t figure;
    init(figure);
    switch (event.task)
    {
        case LOAD:
            return_code = load_figure(figure, event.filename);
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

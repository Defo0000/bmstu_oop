#include "event.h"
#include "figure.h"

rc_t event_handler(const event_t event)
{
    rc_t return_code = OK;
    static figure_t figure = init();
    switch (event.task)
    {
        case LOAD:
            return_code = load_figure(figure, event.filename);
            break;
        case SCALE:
            return_code = scale_figure(figure, event.scale);
            break;
        case MOVE:
            return_code = move_figure(figure, event.move);
            break;
        case ROTATE:
            return_code = rotate_figure(figure, event.rotate);
            break;
        case DRAW:
            return_code = draw_figure(figure, event.plane);
            break;
        case QUIT:
            free_figure(figure);
            break;
        default:
            return_code = ERR_UNKNOWN_CMD;
    }
    return return_code;
}

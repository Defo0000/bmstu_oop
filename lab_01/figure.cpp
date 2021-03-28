#include "figure.h"

figure_t& init()
{
    static figure_t figure;

    figure.points.arr = nullptr;
    figure.points.size = 0;

    figure.center.x = 0;
    figure.center.y = 0;
    figure.center.z = 0;

    figure.links.arr = nullptr;
    figure.links.size = 0;

    return figure;
}

rc_t load_cur_figure(figure_t& figure, FILE *f)
{
    rc_t return_code = OK;

    return return_code;
}

rc_t load_figure(figure_t &figure, filename_t name)
{
    FILE *f = fopen(name, "r");
    if (!f)
    {
        return ERR_FILE;
    }
    rc_t return_code = OK;
    figure_t cur_figure = init();
    return_code = load_cur_figure(cur_figure, f);
    return return_code;
}

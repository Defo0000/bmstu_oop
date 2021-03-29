#include "figure.h"

rc_t scale_figure(figure_t &figure, const scale_t params)
{
    rc_t return_code = scale_points(figure.points, figure.center, params);
    return return_code;
}

rc_t move_figure(figure_t &figure, const move_t params)
{
    rc_t return_code = move_points(figure.points, params);
    return return_code;
}

rc_t rotate_figure(figure_t &figure, const rotate_t params)
{
    rc_t return_code = rotate_points(figure.points, figure.center, params);
    return return_code;
}

rc_t load_temp_figure(figure_t& figure, FILE *f)
{
    rc_t return_code = OK;
    if (!(return_code = get_points(figure.points, f)))
    {
        return_code = get_links(figure.links, f);
        if (return_code)
        {
            free_points(figure.points);
        }
        return_code = OK;
    }
    return return_code;
}

rc_t load_figure(figure_t &figure, filename_t name)
{
    rc_t return_code = OK;
    FILE *f = fopen(name, "r");
    if (!f)
    {
        return_code = ERR_FILE;
    }
    if (!return_code)
    {
        figure_t temp_figure;
        init(temp_figure);
        return_code = load_temp_figure(temp_figure, f);
        fclose(f);
        if (!return_code)
        {
            free_figure(figure);
            figure = temp_figure;
        }
    }
    return return_code;
}

rc_t draw_figure(const figure_t figure, const plane_t plane)
{
    rc_t return_code = OK;
    plane.scene->clear();
    return_code = draw_links(figure.links, figure.points, plane);
    return return_code;
}

void free_figure(figure_t& figure)
{
    free_points(figure.points);
    free_links(figure.links);
}

void init(figure_t& figure)
{
    init_parr(figure.points);
    init_larr(figure.links);
    init_point(figure.center);
}

void init_parr(parr_t& points)
{
    points.arr = nullptr;
    points.size = 0;
}

void init_larr(larr_t& links)
{
    links.arr = nullptr;
    links.size = 0;
}

void init_point(point_t &point)
{
    point.x = 0;
    point.y = 0;
    point.z = 0;
}

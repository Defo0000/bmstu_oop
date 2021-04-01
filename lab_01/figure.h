#ifndef FIGURE_H
#define FIGURE_H

#include <cstdio>

#include "event.h"
#include "point.h"
#include "link.h"

typedef struct
{
    parr_t points;
    larr_t links;
    point_t center;
} figure_t;

figure_t &init();
void init_point(point_t& point);
void init_parr(parr_t& points);
void init_larr(larr_t& links);
rc_t load_figure(figure_t &figure, filename_t name);
void free_figure(figure_t& figure);
rc_t draw_figure(const figure_t figure, const plane_t plane);

rc_t scale_figure(figure_t &figure, const scale_t params);
rc_t move_figure(figure_t &figure, const move_t params);
rc_t rotate_figure(figure_t &figure, const rotate_t params);

#endif // FIGURE_H

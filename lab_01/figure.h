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

void init(figure_t& figure);
void init_point(point_t& point);
void init_parr(parr_t& points);
void init_larr(larr_t& links);
rc_t load_figure(figure_t &figure, filename_t name);
void free_figure(figure_t& figure);

#endif // FIGURE_H

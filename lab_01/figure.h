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

figure_t& init();
rc_t load_figure(figure_t &figure, filename_t name);

#endif // FIGURE_H

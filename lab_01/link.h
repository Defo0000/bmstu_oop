#ifndef LINK_H
#define LINK_H

#include "rc.h"
#include "point.h"
#include <QtWidgets>

typedef struct
{
    QGraphicsScene *scene;
    double width;
    double height;
} plane_t;

typedef struct
{
    size_t src;
    size_t dst;
} link_t;

typedef struct
{
    size_t size;
    link_t *arr;
} larr_t;

rc_t get_links(larr_t& links, FILE *f);
void free_links(larr_t& links);
rc_t draw_links(const larr_t links, const parr_t points, const plane_t plane);

#endif // LINK_H

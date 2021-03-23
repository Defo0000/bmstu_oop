#ifndef ITEMS_H
#define ITEMS_H

struct point
{
    double x, y, z;
};
using point_t = struct point;

struct link
{
    int src, dst;
};
using link_t = struct link;

struct parr
{
    point_t *arr;
    size_t size;
    point_t center;
};
using parr_t = struct parr;

struct larr
{
    link_t *arr;
    size_t size;
};
using larr_t = struct larr;

#endif // ITEMS_H

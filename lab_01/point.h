#ifndef POINT_H
#define POINT_H

#include "rc.h"

typedef struct
{
    double x;
    double y;
    double z;
} point_t;

typedef struct
{
    double kx;
    double ky;
    double kz;
} scale_t;

typedef struct
{
    double dx;
    double dy;
    double dz;
} move_t;

typedef struct
{
    double rx;
    double ry;
    double rz;
} rotate_t;

typedef struct
{
    size_t size;
    point_t *arr;
} parr_t;

rc_t get_points(parr_t& points, FILE *f);
void free_points(parr_t& points);

#endif // POINT_H

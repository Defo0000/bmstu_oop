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

rc_t scale_points(parr_t &points, point_t &center, const scale_t &params);
static void scale_point(point_t &point, const point_t center, const scale_t &params);

rc_t move_points(parr_t &points, const move_t &params);
static void move_point(point_t &point, const move_t &params);

rc_t rotate_points(parr_t &points, point_t &center, const rotate_t &params);
static void x_rotate_point(point_t &point, point_t &center, const double angle);
static void y_rotate_point(point_t &point, point_t &center, const double angle);
static void z_rotate_point(point_t &point, point_t &center, const double angle);

#endif // POINT_H

#include "point.h"
#include "figure.h"

void free_points(parr_t& points)
{
    free(points.arr);
}

static rc_t read_point(point_t& point, FILE *f)
{
    rc_t return_code = OK;
    if (!f)
    {
        return_code = ERR_FILE;
    }
    if (!return_code && fscanf(f, "%lf%lf%lf", &point.x, &point.y, &point.z) != 3)
    {
        return_code = ERR_READ;
    }
    return return_code;
}

static rc_t read_points(point_t *const arr, const size_t size, FILE *f)
{
    rc_t return_code = OK;
    if (!arr || !size)
    {
        return_code = ERR_DATA;
    }
    for (size_t i = 0; i < size && ! return_code; i++)
    {
        return_code = read_point(arr[i], f);
    }
    return return_code;
}

static rc_t allocate_points(parr_t& points)
{
    rc_t return_code = OK;
    point_t *temp_parr = (point_t *) malloc(sizeof(point_t) * points.size);
    if (!temp_parr)
    {
        return_code = ERR_ALLOC;
    }
    if (!return_code)
    {
        points.arr = temp_parr;
    }
    return return_code;
}

static rc_t read_amount(parr_t& points, FILE *f)
{
    rc_t return_code = OK;
    if (fscanf(f, "%ld", &(points.size)) != 1)
    {
        return_code = ERR_READ;
    }
    return return_code;
}

rc_t get_points(parr_t& points, FILE *f)
{
    rc_t return_code = OK;
    if (!f)
    {
        return_code = ERR_FILE;
    }

    if (!return_code)
    {
        if (!(return_code = read_amount(points, f)) && !(return_code = allocate_points(points)))
        {
            if ((return_code = read_points(points.arr, points.size, f)))
            {
                free_points(points);
            }
        }
    }
    return return_code;
}

static void scale_point(point_t &point, const point_t center, const scale_t &params)
{
    point.x = center.x + params.kx * (point.x - center.x);
    point.y = center.y + params.ky * (point.y - center.y);
    point.z = center.z + params.kz * (point.z - center.z);
}

rc_t scale_points(parr_t &points, point_t &center, const scale_t &params)
{
    rc_t return_code = OK;
    if (!points.arr)
    {
        return_code = ERR_DATA;
    }
    else for (size_t i = 0; i < points.size; i++)
    {
        scale_point(points.arr[i], center, params);
    }
    return return_code;
}

static void move_point(point_t &point, const move_t &params)
{
    point.x += params.dx;
    point.y += params.dy;
    point.z += params.dz;
}

rc_t move_points(parr_t &points, const move_t &params)
{
    rc_t return_code = OK;
    if (!points.arr)
    {
        return_code = ERR_DATA;
    }
    else for (size_t i = 0; i < points.size; i++)
    {
        move_point(points.arr[i], params);
    }
    return return_code;
}

double to_radians(const double angle_degrees)
{
    return angle_degrees * M_PI / 180;
}

static void x_rotate_point(point_t &point, point_t &center, const double angle)
{
    double cos_a = cos(to_radians(angle));
    double sin_a = sin(to_radians(angle));
    point_t temp = point;

    //move_point(temp, -center);

    temp.y = point.y * cos_a - point.z * sin_a;
    temp.z = point.y * sin_a + point.z * cos_a;

    //move_point(temp, center);
    point = temp;
}

static void y_rotate_point(point_t &point, point_t &center, const double angle)
{
    double cos_a = cos(to_radians(angle));
    double sin_a = sin(to_radians(angle));
    point_t temp = point;

    //move_point(temp, -center);

    temp.x = point.x * cos_a + point.z * sin_a;
    temp.z = -point.x * sin_a + point.z * cos_a;

    //move_point(temp, center);
    point = temp;
}

static void z_rotate_point(point_t &point, point_t &center, const double angle)
{
    double cos_a = cos(to_radians(angle));
    double sin_a = sin(to_radians(angle));
    point_t temp = point;

    //move_point(temp, -center);

    temp.x = point.x * cos_a - point.y * sin_a;
    temp.y = point.x * sin_a + point.y * cos_a;

    //move_point(temp, center);
    point = temp;
}

rc_t rotate_points(parr_t &points, point_t &center, const rotate_t &params)
{
    rc_t return_code = OK;
    if (!points.arr)
    {
        return_code = ERR_DATA;
    }
    else for (size_t i = 0; i < points.size; i++)
    {
        x_rotate_point(points.arr[i], center, params.rx);
        y_rotate_point(points.arr[i], center, params.ry);
        z_rotate_point(points.arr[i], center, params.rz);
    }
    return return_code;
}

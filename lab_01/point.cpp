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

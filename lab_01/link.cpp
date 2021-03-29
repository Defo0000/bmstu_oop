#include "point.h"
#include "link.h"

void free_links(larr_t& links)
{
    free(links.arr);
}

static rc_t read_link(link_t& link, FILE *f)
{
    rc_t return_code = OK;
    if (!f)
    {
        return_code = ERR_FILE;
    }
    if (!return_code && fscanf(f, "%ld%ld", &(link.dst), &(link.src)) != 2)
    {
        return_code = ERR_READ;
    }
    return return_code;
}

static rc_t read_links(link_t *const arr, const size_t size, FILE *f)
{
    rc_t return_code = OK;
    if (!arr || !size)
    {
        return_code = ERR_DATA;
    }
    for (size_t i = 0; i < size && ! return_code; i++)
    {
        return_code = read_link(arr[i], f);
    }
    return return_code;
}

static rc_t allocate_links(larr_t& links)
{
    rc_t return_code = OK;
    link_t *temp_larr = (link_t *) malloc(sizeof(link_t) * links.size);
    if (!temp_larr)
    {
        return_code = ERR_ALLOC;
    }
    if (!return_code)
    {
        links.arr = temp_larr;
    }
    return return_code;
}

static rc_t read_amount(larr_t& links, FILE *f)
{
    rc_t return_code = OK;
    if (fscanf(f, "%ld", &(links.size)) != 1)
    {
        return_code = ERR_READ;
    }
    return return_code;
}

rc_t get_links(larr_t& links, FILE *f)
{
    rc_t return_code = OK;
    if (!f)
    {
        return_code = ERR_FILE;
    }
    if (!return_code)
    {
        if (!(return_code = read_amount(links, f)) && !(return_code = allocate_links(links)))
        {
            if ((return_code = read_links(links.arr, links.size, f)))
            {
                free_links(links);
            }
        }
    }
    return return_code;
}

static void draw_edge(const point_t src, const point_t dst, const plane_t plane)
{
    plane.scene->addLine(src.x, src.y, dst.x, dst.y);
}

rc_t draw_links(const larr_t links, const parr_t points, const plane_t plane)
{
    rc_t return_code = OK;

    if (!links.arr || !points.arr)
    {
        return_code = ERR_DATA;
    }

    for (size_t i = 0; i < links.size && !return_code; i++)
    {
        draw_edge(points.arr[links.arr[i].dst], points.arr[links.arr[i].src], plane);
    }

    return return_code;
}

#ifndef LINK_H
#define LINK_H

#include "rc.h"

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

#endif // LINK_H

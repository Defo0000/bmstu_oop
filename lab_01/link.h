#ifndef LINK_H
#define LINK_H

typedef struct
{
    unsigned int l_src;
    unsigned int l_dst;
} link_t;

typedef struct
{
    size_t size;
    link_t *arr;
} larr_t;

#endif // LINK_H

#ifndef LINK_H
#define LINK_H

typedef struct
{
    unsigned int l1;
    unsigned int l2;
} link_t;

typedef struct
{
    size_t size;
    link_t *larr;
} larr_t;

#endif // LINK_H

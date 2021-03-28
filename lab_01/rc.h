#ifndef RC_H
#define RC_H

#include <cstddef>
#include <cstdio>
#include <cstdlib>

typedef enum
{
    OK,
    ERR_FILE,
    ERR_ALLOC,
    ERR_READ,
    ERR_SIZE,
    ERR_DATA,
    ERR_UNKNOWN_CMD,
} rc_t;

#endif // RC_H

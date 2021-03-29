#ifndef RC_H
#define RC_H

#include <cstddef>
#include <cstdio>
#include <cstdlib>

#include <QMessageBox>

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

void handle_return_code(const rc_t code);

#endif // RC_H

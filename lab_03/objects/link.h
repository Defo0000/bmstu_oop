#ifndef LINK_H
#define LINK_H

#include <stdlib.h>

class link
{
public:
    link();
    link(size_t begin, size_t end);
    explicit link(const link &_link);

    ~link() = default;

    link& operator=(const link &_link);

    size_t get_begin() const;
    size_t get_end() const;

    void set_begin(size_t begin);
    void set_end(size_t end);

private:
    size_t _begin;
    size_t _end;
};

#endif // LINK_H

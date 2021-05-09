#ifndef BASE_CONTAINER_H
#define BASE_CONTAINER_H

class base_container
{
public:
    base_container();

    virtual ~base_container() = default;

    virtual bool is_empty() const;

    virtual void clear() = 0;

    size_t get_size() const;

protected:
    size_t size;
};

#include "base_container.hpp"

#endif

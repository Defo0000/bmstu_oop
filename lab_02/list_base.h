#ifndef LIST_BASE_H
#define LIST_BASE_H

class list_base
{
public:
    list_base();
    virtual ~list_base() = default;

    virtual bool is_empty() const;

    size_t size() const;

protected:
    size_t _size;
};

#include "list_base.hpp"

#endif // LIST_BASE_H

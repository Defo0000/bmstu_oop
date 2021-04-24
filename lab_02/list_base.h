#ifndef LIST_BASE_H
#define LIST_BASE_H

#include <iostream>

class list_base {

public:
    list_base();
    virtual ~list_base();
    virtual bool is_empty() const = 0;
    size_t size() const;

protected:
    size_t size;
};

#endif // LIST_BASE_H

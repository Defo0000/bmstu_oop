#ifndef LIST_BASE_H
#define LIST_BASE_H

#include <iostream>

class Base_List {

public:
    Base_List();
    virtual ~Base_List();
    virtual bool is_empty() const = 0;
    size_t size() const;

protected:
    size_t size;
};

#endif // LIST_BASE_H

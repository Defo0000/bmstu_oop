#ifndef LIST_H
#define LIST_H

#include "list_base.h"
#include "list_node.h"

template <typename T>
class list: public list_base
{
public:
    list();

    list(list<T> &list);
    list<T> &operator = (const list<T> &list);

    list(list<T> &&list);
    list<T> &operator = (const list<T> &&list);

    list(std::initializer_list<T> _list);
    list(const T *arr, const int size);

    virtual bool is_empty() const;
    virtual void clear();

    ~list() = default;

private:
    size_t size;
    std::shared_ptr<list_node<T>> head;
    std::shared_ptr<list_node<T>> tail;
}

#endif // LIST_H

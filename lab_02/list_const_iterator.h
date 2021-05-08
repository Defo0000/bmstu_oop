#ifndef LIST_CONST_ITERATOR_H
#define LIST_CONST_ITERATOR_H

#include "list_node.h"
#include "list_iterator.h"

template <typename T>
class list_const_iterator : std::iterator<std::input_iterator_tag, T>
{
public:
    list_const_iterator();
    list_const_iterator(const std::shared_ptr<list_node<T>> &node);
    list_const_iterator(const list_const_iterator<T> &iterator);

    ~list_const_iterator() = default;

    void next();

    operator bool() const;

    const list_node<T> *operator ->() const;
    const list_node<T> &operator *() const;

    list_const_iterator<T> operator = (const list_iterator<T> &iterator);
    list_const_iterator<T> &operator ++ ();
    list_const_iterator<T> operator ++ (int);

    list_const_iterator<T> &operator += (const size_t size);
    list_const_iterator<T> operator + (const size_t size) const;

    bool operator != (const list_const_iterator<T> &iterator) const;
    bool operator == (const list_const_iterator<T> &iterator) const;

private:
    std::weak_ptr<list_node<T>> ptr;
};

#include "list_const_iterator.hpp"

#endif // LIST_CONST_ITERATOR_H

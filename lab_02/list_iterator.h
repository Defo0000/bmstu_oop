#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include <iterator>
#include "list_node.h"

template <typename T>
class list_iterator : std::iterator<std::input_iterator_tag, T>
{
public:
    list_iterator();
    list_iterator(const std::shared_ptr<list_node<T>> &node);
    list_iterator(const list_iterator<T> &iterator);

    virtual ~list_iterator() = default;

    operator bool() const;
    virtual void go_to_next();

    list_node<T> *operator ->();
    const list_node<T> *operator ->() const;

    list_node<T> &operator *();
    const list_node<T> &operator *() const;

    list_iterator<T> &operator += (const size_t &size);
    list_iterator<T> operator + (const size_t &size) const;
    list_iterator<T> operator = (const list_iterator<T> &iterator);
    list_iterator<T> &operator ++ ();
    list_iterator<T> operator ++ (int);

    bool operator != (const list_iterator<T> &iterator) const;
    bool operator == (const list_iterator<T> &iterator) const;

private:
    std::weak_ptr<list_node<T>> ptr;
};

#include "list_iterator.hpp"

#endif // LIST_ITERATOR_H

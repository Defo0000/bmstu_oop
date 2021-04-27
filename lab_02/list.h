#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include "list_base.h"
#include "list_iterator.h"
#include "list_const_iterator.h"

template <typename T>
class list: public list_base
{
public:
    list();
    list(list<T> &list);
    list(list<T> &&list);
    list(const T *arr, const size_t len);

    list<T> &operator = (const list<T> &list);
    list<T> &operator = (const list<T> &&list);

    list(std::initializer_list<T> _list);
    list(const T *arr, const int size);

    virtual ~list() = default;

    void reverse();

    T remove(const list_iterator<T> &iterator);
    list<T> &insert(const list_iterator<T> &iterator, const T &data);

    list<T> &operator += (const list<T> &list);
    list<T> &operator += (const T &data);

    list<T> &operator + (const list<T> &list);
    list<T> &operator + (const T &data);

    list<T> &extend(const list<T> &list_to_append);

    list_iterator<T> push_back(const T &data);
    list_iterator<T> push_back(const std::shared_ptr<list_node<T>> &node);
    list_iterator<T> push_back(const list<T> &list);

    T pop_front();
    T pop_back();

    list_iterator<T> begin();
    list_iterator<T> end();

    list_const_iterator<T> cbegin() const;
    list_const_iterator<T> cend() const;

    bool operator == (const list<T> &list) const;
    bool operator != (const list<T> &list) const;

protected:
    std::shared_ptr<list_node<T>> get_head();
    std::shared_ptr<list_node<T>> get_tail();

private:
    std::shared_ptr<list_node<T>> head;
    std::shared_ptr<list_node<T>> tail;
};

#include "list.hpp"

#endif // LIST_H

#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include "errors.h"
#include "list_base.h"
#include "list_iterator.h"
#include "list_const_iterator.h"

template <typename T>
class list: public list_base
{
public:
    list();
    list(list<T> &_list);
    list(list<T> &&_list);
    list(const T *arr, const size_t len);
    list(std::initializer_list<T> _list);

    virtual ~list() = default;

    void reverse();
    virtual void clear();

    T remove(const list_iterator<T> &iterator);
    void remove(const list_iterator<T> &start, const list_iterator<T> &end);

    list_iterator<T> insert(const list_iterator<T> &iterator, const T &data);
    list_iterator<T> insert(const list_iterator<T> &iterator, const list<T> &list);
    list_iterator<T> insert(const list_const_iterator<T> &iterator, const T &data);
    list_iterator<T> insert(const list_const_iterator<T> &iterator, const list<T> &list);

    list<T> &merge(const list<T> &list);

    list_iterator<T> push_back(const T &data);
    list_iterator<T> push_back(list<T> const &list);

    list_iterator<T> push_front(const T &data);
    list_iterator<T> push_front(list<T> const &list);

    T pop_front();
    T pop_back();

    list_iterator<T> begin();
    list_iterator<T> end();

    list_const_iterator<T> cbegin() const;
    list_const_iterator<T> cend() const;

    list<T> &operator = (const list<T> &list);
    list<T> &operator = (const list<T> &&list);

    list<T> &operator += (const list<T> &list);
    list<T> &operator += (const T &data);

    list<T> &operator + (const list<T> &list);
    list<T> &operator + (const T &data);

    bool operator == (const list<T> &list) const;
    bool operator != (const list<T> &list) const;

protected:
    list_iterator<T> push_back(const std::shared_ptr<list_node<T>> &node);
    list_iterator<T> push_front(const std::shared_ptr<list_node<T>> &node);
    std::shared_ptr<list_node<T>> get_head();
    std::shared_ptr<list_node<T>> get_tail();

private:
    std::shared_ptr<list_node<T>> head;
    std::shared_ptr<list_node<T>> tail;
};

#include "list.hpp"

#endif // LIST_H

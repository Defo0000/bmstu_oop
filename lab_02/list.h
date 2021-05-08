#ifndef LIST_H
#define LIST_H

#include <initializer_list>
#include <memory>
#include "errors.h"
#include "base_container.h"
#include "list_iterator.h"
#include "list_const_iterator.h"

template <typename T>
class list: public base_container
{
public:
    list();
    explicit list(list<T> &list);
    list(list<T> &&list);
    list(const T *arr, const size_t len) noexcept;
    list(std::initializer_list<T> list);

    template <typename T_>
    list(T_ begin, T_ end);

    list<T> &operator = (const list<T> &list);
    list<T> &operator = (const list<T> &&list);
    list<T> &operator=(std::initializer_list<T> list);

    ~list() = default;

    virtual void clear();
    virtual bool is_empty() const;

    list_iterator<T> insert(const list_iterator<T> iterator, const T data);
    list_iterator<T> insert(const list_iterator<T> iterator, const list<T> &list);

    list_iterator<T> insert(const list_const_iterator<T> iterator, const T data);
    list_iterator<T> insert(const list_const_iterator<T> iterator, const list<T> &list);

    list_iterator<T> push_back(const T &data);
    list_iterator<T> push_back(list<T> const &list);

    list_iterator<T> push_front(const T &data);
    list_iterator<T> push_front(list<T> const &list);

    T pop();

    T remove(const list_iterator<T> iterator);

    void reverse();

    list<T> &merge(const list<T> &list);

    list<T> &operator += (const list<T> &list);
    list<T> &operator += (const T &data);

    list<T> &operator + (const list<T> &list);
    list<T> &operator + (const T &data);

    bool operator == (const list<T> &list) const;
    bool operator != (const list<T> &list) const;

    list_iterator<T> begin();
    list_iterator<T> end();

    list_const_iterator<T> cbegin() const;
    list_const_iterator<T> cend() const;

    list_const_iterator<T> begin() const;
    list_const_iterator<T> end() const;

protected:
    std::shared_ptr<list_node<T>> get_head();
    std::shared_ptr<list_node<T>> get_tail();
    list_iterator<T> push_back(const std::shared_ptr<list_node<T>> &node);
    list_iterator<T> push_front(const std::shared_ptr<list_node<T>> &node);

private:
    std::shared_ptr<list_node<T>> head;
    std::shared_ptr<list_node<T>> tail;
};

#include "list.hpp"

#endif // LIST_HPP

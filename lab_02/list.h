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

    list<T> &extend(const list<T> &list_to_append);

    //list_iterator<T> push_back(const T &data);
    //list_iterator<T> push_back(const list<T> &list);

    T pop_front();
    T pop_back();

    //list_iterator<T> begin();
    //const_list_iterator<T> cbegin() const;

    //list_iterator<T> end();
    //const_list_iterator<T> cend() const;

    virtual bool is_empty() const;
    virtual void clear();

    ~list() = default;

private:
    std::shared_ptr<list_node<T>> head;
    std::shared_ptr<list_node<T>> tail;
};

#endif // LIST_H

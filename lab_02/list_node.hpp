#ifndef _LISTNODE_HPP_
#define _LISTNODE_HPP_

#include "list_node.h"

template <typename T>
list_node<T>::list_node(): data(0), next(nullptr) {}

template <typename T>
list_node<T>::list_node(const T &data) : data(data), next(nullptr) {}

template <typename T>
list_node<T>::list_node(const shared_ptr<list_node<T>> &node)
{
    this->data = node->data;
    this->next = node->next;
}

template <typename T>
list_node<T>::~list_node()
{
    this->data = 0;
    this->next = nullptr;
}

template <typename T>
void list_node<T>::set(const T &data)
{
    this->data = data;
}

template <typename T>
void list_node<T>::set_next(const list_node<T> &node)
{
    shared_ptr<list_node<T>> node_ptr(node);
    this->next = node_ptr;
}

template <typename T>
void list_node<T>::set_next(const shared_ptr<list_node<T>> &node)
{
    this->next = node;
}

template <typename T>
T list_node<T>::get() const
{
    return this->data;
}

template <typename T>
T &list_node<T>::get_ptr()
{
    return this->data;
}

template <typename T>
shared_ptr<list_node<T>> list_node<T>::get_next(void) const
{
    return this->next;
}

#endif

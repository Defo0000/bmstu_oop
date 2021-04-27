#ifndef _LIST_HPP_
#define _LIST_HPP_

#include "list.h"

template <typename T>
list<T>::list() : head(nullptr), tail(nullptr) {}

template <typename T>
bool list<T>::is_empty() const
{
    return this->head == nullptr;
}

template <typename T>
bool list<T>::clear()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->_size = 0;
}

#endif

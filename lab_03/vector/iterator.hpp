#pragma once

#include "vector.hpp"

template <typename T>
class iterator : public std::iterator<std::input_iterator_tag, T>
{
public:
    iterator(const iterator<T> &iterator);
    iterator(const vector<T> &vector);

    T &operator*();
    const T &operator*() const;

    T *operator->();
    const T *operator->() const;

    operator bool() const;

    iterator<T> &operator+=(size_t len);
    iterator<T> operator+(size_t len) const;

    iterator<T> &operator++();
    iterator<T> operator++(int);

    bool operator==(const iterator<T> &iterator) const;
    bool operator!=(const iterator<T> &iterator) const;

private:
    size_t cur_index;
    size_t vector_size;
    std::weak_ptr<T[]> ptr;
};


template <typename T>
iterator<T>::iterator(const iterator<T> &iterator)
{
    this->ptr = iterator.ptr;
    this->cur_index = iterator.cur_index;
    this->vector_size = iterator.vector_size;
}

template <typename T>
iterator<T>::iterator(const vector<T> &vector)
{
    this->ptr = vector.value;
    this->vector_size = vector.size();
    this->cur_index = 0;
}

template <typename T>
T &iterator<T>::operator*()
{
    return *get_current();
}

template <typename T>
const T &iterator<T>::operator*() const
{
    return get_current();
}

template <typename T>
T *iterator<T>::operator->()
{
    return get_current();
}

template <typename T>
const T *iterator<T>::operator->() const
{
    return get_current();
}

#pragma once

#include <initializer_list>
#include <stdlib.h>

template <typename T>
class vector : base_container
{
public:
    vector();
    vector(size_t len, const T data);
    vector(const T *array, size_t len);
    vector(const std::initializer_list<T> &list);
    vector(const vector<T> &vec);

    virtual ~vector() = default;

    T at(size_t index) const;

    vector<T> &push_back(const T data);
    vector<T> &operator += (const T data);

    iterator<T> begin();
    iterator<T> end();

    const iterator<T> begin() const;
    const iterator<T> end() const;

private:

};

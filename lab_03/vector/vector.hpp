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

    virtual size_t get_size() const;

protected:
};

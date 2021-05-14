#pragma once

template <typename T>
class base_container
{

public:
    base_container() = default;
    ~base_container() = default;
    virtual void clean() = 0;
    virtual size_t size() const;

protected:
    size_t _size;
};

template <typename T>
size_t base_container<T>::size() const { return this->_size; }

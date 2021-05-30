#pragma once

template <typename T>
class base_container
{

public:
    base_container() = default;
    ~base_container() = default;
    virtual void clean() = 0;
    virtual size_t size() const;
    virtual bool is_empty() const;

protected:
    size_t _size;
};

template <typename T>
size_t base_container<T>::size() const { return this->_size; }

template <typename T>
bool base_container<T>::is_empty() const { return this->_size == 0 ? true : false; }

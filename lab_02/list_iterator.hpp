#ifndef _LISTNODE_HPP_
#define _LISTNODE_HPP_

template <typename T>
list_iterator<T>::list_iterator()
{
    this->ptr.lock() = nullptr;
}

template <typename T>
list_iterator<T>::list_iterator(const std::shared_ptr<list_node<T>> &node)
{
    this->ptr = node;
}

template <typename T>
list_iterator<T>::list_iterator(const list_iterator<T> &iterator)
{
    this->ptr = iterator.ptr.lock();
}

template <typename T>
void list_iterator<T>::go_to_next(void)
{
    this->ptr = this->ptr.lock()->get_next();
}

template <typename T>
list_node<T> *list_iterator<T>::operator ->()
{
    return this->ptr.lock().get();
}

template <typename T>
const list_node<T> *list_iterator<T>::operator ->() const
{
    return this->ptr.lock().get();
}

template <typename T>
list_node<T> &list_iterator<T>::operator *()
{
    return *this->ptr.lock();
}

template <typename T>
const list_node<T> &list_iterator<T>::operator *() const
{
    return *this->ptr.lock();
}

template <typename T>
list_iterator<T>::operator bool() const
{
    return this->ptr.lock() != nullptr;
}

template <typename T>
list_iterator<T> &list_iterator<T>::operator += (const size_t &size)
{
    for (size_t i = 0; i < size; i++)
    {
        this->next();
    }
    return *this;
}

template <typename T>
list_iterator<T> list_iterator<T>::operator + (const int &size) const
{
    list_iterator<T> new_iterator(*this);
    new_iterator += size;
    return new_iterator;
}

template <typename T>
list_iterator<T> list_iterator<T>::operator = (const list_iterator<T> &iterator)
{
    this->ptr = iterator.ptr.lock();
    return *this;
}

template <typename T>
list_iterator<T> &list_iterator<T>::operator ++ ()
{
    this->next();
    return *this;
}

template <typename T>
bool list_iterator<T>::operator != (const list_iterator<T> &iterator) const
{
    return this->ptr.lock() != iterator.ptr.lock();
}

template <typename T>
bool list_iterator<T>::operator == (const list_iterator<T> &iterator) const
{
    return this->ptr.lock() == iterator.ptr.lock();
}

#endif

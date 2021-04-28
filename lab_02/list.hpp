#ifndef _LIST_HPP_
#define _LIST_HPP_

template <typename T>
list<T>::list()
{
    this->_size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T>
list<T>::list(list<T> &list)
{
    this->_size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    for (auto node: list)
    {
        std::shared_ptr<list_node<T>> temp_node = nullptr;
        temp_node = std::shared_ptr<list_node<T>>(new list_node<T>);
        temp_node->set(node.get());
        this->push_back(temp_node);
    }
}

template <typename T>
list<T>::list(list<T> &&list)
{
    this->_size = list.size;
    this->head = list.head;
    this->tail = list.tail;
}

template <typename T>
list<T>::list(const T *arr, const size_t len)
{
    this->_size = 0;
    this->head = nullptr;
    this->tail = nullptr;
    for (size_t i = 0; i < len; i++)
    {
        this->push_back(arr[i]);
    }
}

template <typename T>
list_iterator<T> list<T>::push_back(const T &data)
{
    std::shared_ptr<list_node<T>> node = nullptr;
    node = std::shared_ptr<list_node<T>>(new list_node<T>);
    node->set(data);
    return this->push_back(node);
}

template <typename T>
list_iterator<T> list<T>::push_back(const std::shared_ptr<list_node<T>> &node)
{
    std::shared_ptr<list_node<T>> temp_node = nullptr;
    temp_node = std::shared_ptr<list_node<T>>(new list_node<T>);
    temp_node->set(node->get());

    if (!this->_size)
    {
        this->head = temp_node;
        this->tail = temp_node;
    }
    else
    {
        this->tail->set_next(temp_node);
        this->tail = temp_node;
    }

    this->tail->set_next(nullptr);
    this->_size++;

    list_iterator<T> iterator(this->tail);
    return iterator;
}

template <typename T>
list_iterator<T> list<T>::begin(void)
{
    return list_iterator<T>(this->head);
}

template <typename T>
list_const_iterator<T> list<T>::cbegin(void) const
{
    return list_const_iterator<T>(this->head);
}

template <typename T>
list_iterator<T> list<T>::end(void)
{
    return ++list_iterator<T>(this->tail);
}

template <typename T>
list_const_iterator<T> list<T>::cend(void) const
{
    return ++list_const_iterator<T>(this->tail);
}

#endif

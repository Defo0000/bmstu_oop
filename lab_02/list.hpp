#ifndef _LIST_HPP_
#define _LIST_HPP_

template <typename T>
list<T>::list()
{
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
}

template <typename T>
list<T>::list(list<T> &list)
{
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    for (auto node: list)
    {
        std::shared_ptr<list_node<T>> temp_node = nullptr;

        try {

            temp_node = std::shared_ptr<list_node<T>>(new list_node<T>);

        } catch (std::bad_alloc &error) {

            auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            throw memory_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);

        }

        temp_node->set(node.get());
        this->push_back(temp_node);
    }
}

template <typename T>
list<T>::list(list<T> &&list)
{
    this->size = list.size;
    this->head = list.head;
    this->tail = list.tail;
}

template <typename T>
list<T>::list(const T *arr, const size_t len)
{
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
    for (size_t i = 0; i < len; i++)
    {
        this->push_back(arr[i]);
    }
}

template <typename T>
list<T>::list(std::initializer_list<T> nodes)
{
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    for (auto node: nodes)
    {
        this->push_back(node);
    }
}

template <typename T>
list_iterator<T> list<T>::push_back(const T &data)
{
    std::shared_ptr<list_node<T>> node = nullptr;
    try {

        node = std::shared_ptr<list_node<T>>(new list_node<T>);

    }
    catch (std::bad_alloc &error)
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw memory_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    node->set(data);
    return this->push_back(node);
}

template <typename T>
list_iterator<T> list<T>::push_back(const list<T> &list)
{
    for (auto cur = list.cbegin(); cur != list.cend(); cur++)
    {
        this->push_back((*cur).get());
    }

    list_iterator<T> iterator(this->tail);
    return iterator;
}

template <typename T>
list_iterator<T> list<T>::push_back(const std::shared_ptr<list_node<T>> &node)
{
    std::shared_ptr<list_node<T>> temp_node = nullptr;

    try {

        temp_node = std::shared_ptr<list_node<T>>(new list_node<T>);

    } catch (std::bad_alloc &errod) {

        auto _time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw memory_error(__FILE__, ctime(&_time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    temp_node->set(node->get());

    if (this->is_empty())
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
    this->size++;

    list_iterator<T> iterator(this->tail);
    return iterator;
}

template <typename T>
list_iterator<T> list<T>::push_front(const T &data)
{
    std::shared_ptr<list_node<T>> cur_node = nullptr;

    try
    {

        cur_node = std::shared_ptr<list_node<T>>(new list_node<T>);

    } catch (std::bad_alloc &error) {

        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw memory_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);

    }

    cur_node->set(data);
    return this->push_front(cur_node);
}

template <typename T>
list_iterator<T> list<T>::push_front(const list<T> &list)
{
    list_iterator<T> iterator;

    for (size_t i = 0; i < list.size; i++)
    {
        iterator = this->insert(this->begin() + i, (*(list.cbegin() + i)).get());
    }

    return iterator;
}

template <typename T>
list_iterator<T> list<T>::push_front(const std::shared_ptr<list_node<T>> &node)
{
    if (!node)
    {
        auto time    = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw ptr_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    node->set_next(this->head);
    this->head = node;

    if (this->is_empty())
    {
        this->tail = node;
    }

    this->size++;

    list_iterator<T> iterator(node);
    return iterator;
}

template <typename T>
T list<T>::pop_front(void)
{
    if (this->is_empty())
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw empty_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    T data = this->head->get();

    if (this->size == 1)
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else
    {
        this->head = this->head->get_next();
    }

    this->size--;

    return data;
}

template <typename T>
T list<T>::pop_back(void)
{
    if (this->is_empty())
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw empty_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    T data = this->tail->get();

    if (this->size == 1)
    {
        this->head = nullptr;
        this->tail = nullptr;
    }
    else
    {
        std::shared_ptr<list_node<T>> cur = this->head;
        while (cur->get_next() && cur->get_next()->get_next())
        {
            cur = cur->get_next();
        }

        this->tail = cur;
    }

    this->size--;

    return data;
}

template <typename T>
T list<T>::remove(const list_iterator<T> &iterator)
{
    if (iterator.is_nullptr())
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw iterator_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    if (this->is_empty())
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw empty_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    if (iterator == this->begin())
    {
        return pop_front();
    }

    list_iterator<T> temp_iterator = this->begin();

    while ((temp_iterator + 1) != iterator)
    {
        temp_iterator++;
    }

    T data = temp_iterator->get();
    temp_iterator->set_next(iterator->get_next());

    this->size--;

    return data;
}

template <typename T>
list_iterator<T> list<T>::insert(const list_iterator<T> &iterator, const T &data)
{
    if (iterator.is_nullptr())
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw iterator_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    std::shared_ptr<list_node<T>> temp_node = nullptr;

    try
    {

        temp_node = std::shared_ptr<list_node<T>>(new list_node<T>);

    } catch (std::bad_alloc &error) {

        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw memory_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);

    }

    temp_node->set(data);

    list_iterator<T> temp_iterator = this->begin();

    while ((temp_iterator + 1) != iterator)
    {
        temp_iterator++;
    }

    temp_node->set_next(temp_iterator->get_next());
    temp_iterator->set_next(temp_node);

    this->size++;

    list_iterator<T> insert_iterator(temp_node);
    return insert_iterator;
}

template <typename T>
list_iterator<T> list<T>::insert(const list_iterator<T> &iterator, const list<T> &list)
{
    if (iterator.is_nullptr())
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw iterator_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    list_iterator<T> insert_iterator;

    for (size_t i = 0; i < list.size; i++)
    {
        insert_iterator = insert(iterator, (*(list.cbegin() + i)).get());
    }

    return insert_iterator;
}

template <typename T>
list_iterator<T> list<T>::insert(const list_const_iterator<T> &iterator, const T &data)
{
    if (iterator.is_nullptr())
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw iterator_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    std::shared_ptr<list_node<T>> temp_node = nullptr;

    try
    {

        temp_node = std::shared_ptr<list_node<T>>(new list_node<T>);

    } catch (std::bad_alloc &error) {

        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw memory_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);

    }

    temp_node->set(data);

    list_iterator<T> temp_iterator = this->begin();

    while ((temp_iterator + 1) != iterator)
    {
        temp_iterator++;
    }

    temp_node->set_next(temp_iterator->get_next());
    temp_iterator->set_next(temp_node);

    this->size++;

    list_iterator<T> insert_iterator(temp_node);
    return insert_iterator;
}

template <typename T>
list_iterator<T> list<T>::insert(const list_const_iterator<T> &iterator, const list<T> &list)
{
    if (iterator.is_nullptr())
    {
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        throw iterator_error(__FILE__, ctime(&time), typeid(list).name(), __FUNCTION__, __LINE__);
    }

    list_iterator<T> insert_iterator;

    for (size_t i = 0; i < list.size; i++)
    {
        insert_iterator = insert(iterator, (*(list.cbegin() + i)).get());
    }

    return insert_iterator;
}

template <typename T>
void list<T>::clear(void)
{
    while (this->size != 0)
    {
        this->pop_front();
    }
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

template <typename T>
std::shared_ptr<list_node<T>> list<T>::get_head()
{
    return this->head;
}
template <typename T>
std::shared_ptr<list_node<T>> list<T>::get_tail()
{
    return this->tail;
}

template <typename T>
list<T> &list<T>::operator += (const list<T> &list)
{
    this->push_back(list);
    return *this;
}

template <typename T>
list<T> &list<T>::operator += (const T &data)
{
    this->push_back(data);
    return *this;
}

template <typename T>
list<T> &list<T>::operator + (const list<T> &list)
{
    this->push_back(list);
    return *this;
}

template <typename T>
list<T> &list<T>::operator + (const T &data)
{
    this->push_back(data);
    return *this;
}

template <typename T>
list<T> &list<T>::operator = (const list<T> &list)
{
    this->clear();

    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    push_back(list);
    return *this;
}

template <typename T>
list<T> &list<T>::operator = (const list<T> &&list)
{
    this->size = list.size;
    this->head = list.head;
    this->tail = list.tail;
}

template <typename T>
bool list<T>::operator == (const list<T> &list) const
{
    auto this_iterator = this->cbegin();
    auto list_iterator = list.cbegin();

    while (this_iterator != this->cend() && list_iterator != list.cend())
    {
        if (this_iterator->get() != list_iterator->get())
        {
            return false;
        }
        this_iterator++;
        list_iterator++;
    }

    return this->size == list.size;
}

template <typename T>
bool list<T>::operator != (const list<T> &list) const
{
    return !(*this == list);
}

template <typename T>
void list<T>::reverse(void)
{
    std::shared_ptr<list_node<T>> current(this->head);
    std::shared_ptr<list_node<T>> next;
    std::shared_ptr<list_node<T>> prev;

    while (current)
    {
        next = current->get_next();
        current->set_next(prev);
        prev = current;
        current = next;
    }

    prev = this->head;
    this->head = this->tail;
    this->tail = prev;
}

template <typename T>
list<T> &list<T>::merge(const list<T> &list)
{
    this->push_back(list);
    return *this;
}

#endif

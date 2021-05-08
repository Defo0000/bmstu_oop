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
list<T>::list(const T *arr, const size_t len) noexcept
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
list<T>::list(std::initializer_list<T> list)
{
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;

    for (auto node: list)
    {
        this->push_back(node);
    }
}

template <typename T>
template <typename T_>
list<T>::list(T_ begin, T_ end)
{
    for (auto iterator = begin; iterator != end; ++iterator)
    {
        this->append(*iterator);
    }
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
list<T> &list<T>::operator=(std::initializer_list<T> list)
{
    if (this != &&list)
    {
        this->clear();
        this->size = list->size;
        this->head = list->begin;
        this->tail = list->end;

        list->size = 0;
        list->begin = nullptr;
        list->end = nullptr;
    }

    return *this;
}

template <typename T>
bool list<T>::is_empty(void) const
{
    return (this->size == 0) ? true : false;
}

template <typename T>
void list<T>::clear(void)
{
    while (!this->is_empty())
    {
        this->pop();
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
    for (auto temp = list.cbegin(); temp != list.cend(); temp++)
    {
        this->push_back((*temp).get());
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
        auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
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
T list<T>::pop(void)
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
T list<T>::remove(const list_iterator<T> &iterator)
{
    if (iterator)
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
        return pop();
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
    if (iterator)
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
list_iterator<T> list<T>::begin(void)
{
    return list_iterator<T>(this->head);
}

template <typename T>
list_const_iterator<T> list<T>::begin(void) const
{
    return cbegin();
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
list_const_iterator<T> list<T>::end(void) const
{
    return cend();
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
    std::shared_ptr<list_node<T>> cur(this->head);
    std::shared_ptr<list_node<T>> next;
    std::shared_ptr<list_node<T>> prev;

    while (cur)
    {
        next = cur->get_next();
        cur->set_next(prev);
        prev = cur;
        cur = next;
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

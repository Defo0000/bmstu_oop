#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
class list_node
{
public:

    list_node();
    explicit list_node(const T data);
    explicit list_node(const std::shared_ptr<list_node<T>> &node);

    ~list_node() = default;

    void set(const T data);
    void set_next(const list_node<T> &node);
    void set_next(const std::shared_ptr<list_node<T>> &node);

    T get() const;
    T &get_ptr();
    std::shared_ptr<list_node<T>> get_next() const;

    bool operator == (const std::shared_ptr<list_node<T>> &node) const;
    bool operator != (const std::shared_ptr<list_node<T>> &node) const;
    bool operator > (const std::shared_ptr<list_node<T>> &node) const;
    bool operator < (const std::shared_ptr<list_node<T>> &node) const;
    bool operator >= (const std::shared_ptr<list_node<T>> &node) const;
    bool operator <= (const std::shared_ptr<list_node<T>> &node) const;

private:
    T data;
    std::shared_ptr<list_node<T>> next;
};

#include "list_node.hpp"

#endif // LIST_NODE_H

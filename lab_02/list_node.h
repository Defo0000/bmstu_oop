#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
class list_node
{
public:
    list_node();
    list_node(const T &data);
    list_node(const std::shared_ptr<list_node<T>> &node);

    virtual ~list_node();

    void set(const T data);
    T get() const;
    T &get_ptr();

    bool operator == (const std::shared_ptr<list_node<T>> &node) const;
    bool operator != (const std::shared_ptr<list_node<T>> &node) const;
    bool operator > (const std::shared_ptr<list_node<T>> &node) const;
    bool operator < (const std::shared_ptr<list_node<T>> &node) const;
    bool operator >= (const std::shared_ptr<list_node<T>> &node) const;
    bool operator <= (const std::shared_ptr<list_node<T>> &node) const;

private:
    T data;
    std::shared_ptr<list_node<T>> next;
}

#endif // LIST_NODE_H

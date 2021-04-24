#ifndef LIST_NODE_H
#define LIST_NODE_H

template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename T>
class list_node
{
public:
    list_node();
    list_node(const T &data);
    list_node(const shared_ptr<list_node<T>> &node);

    virtual ~list_node();

    void set(const T data);
    void set_next(const list_node<T> &node);
    void set_next(const shared_ptr<list_node<T>> &node);

    T get() const;
    T &get_ptr();
    list_node<T> get_next() const;
    shared_ptr<list_node<T>> get_next() const;

    bool operator == (const shared_ptr<list_node<T>> &node) const;
    bool operator != (const shared_ptr<list_node<T>> &node) const;
    bool operator > (const shared_ptr<list_node<T>> &node) const;
    bool operator < (const shared_ptr<list_node<T>> &node) const;
    bool operator >= (const shared_ptr<list_node<T>> &node) const;
    bool operator <= (const shared_ptr<list_node<T>> &node) const;

private:
    T data;
    shared_ptr<list_node<T>> next;
}

#endif // LIST_NODE_H

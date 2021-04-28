#ifndef LIST_BASE_HPP
#define LIST_BASE_HPP

list_base::list_base() : _size(0) {}

bool list_base::is_empty() const
{
    return _size == 0;
}

size_t list_base::size() const
{
    return _size;
}

#endif

#ifndef BASE_CONTAINER_HPP
#define BASE_CONTAINER_HPP

base_container::base_container() : size(0) {}

bool base_container::is_empty() const
{
    return size == 0 ? true : false;
}

size_t base_container::get_size() const
{
    return size;
}

#endif

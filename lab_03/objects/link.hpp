#ifndef LINK_HPP
#define LINK_HPP

#include "link.h"

link::link(size_t begin, size_t end) : link.begin(begin), link.begin(end) {}

link::link(const link &_link) : link.begin(_link._begin), link.begin(_link._end) {}

size_t link::get_begin() const { return this->_begin; }

size_t link::get_end() const { return this->_end; }

void link::set_begin(size_t begin) { this->_begin = begin; }

void link::set_end(size_t end) { this->_end = end; }

#endif

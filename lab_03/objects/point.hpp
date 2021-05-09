#ifndef POINT_HPP
#define POINT_HPP

#include "point.h"

template <typename T>
point<T>::point() : _x(0), _y(0), _z(0) {}

template <typename T>
point<T>::point(const T x, const T y, const T z) : _x(x), _y(y), _z(z) {}

template <typename T>
point<T>::point(const point<T> &_point) : point(_point._x, _point._y, _point._z) {}

template <typename T>
point<T> &point<T>::operator=(const point<T> &_point)
{
    this->_x = _point.x;
    this->_y = _point.y;
    this->_z = _point.z;

    return *this;
}

template <typename T>
T point<T>::get_x() const { return this->_x; }

template <typename T>
T point<T>::get_y() const { return this->_y; }

template <typename T>
T point<T>::get_z() const { return this->_z; }


template <typename T>
void point<T>::set_x(T x) { this->_x = x; }

template <typename T>
void point<T>::set_y(T y) { this->_y = y; }

template <typename T>
void point<T>::set_z(T z) { this->_z = z; }



#endif

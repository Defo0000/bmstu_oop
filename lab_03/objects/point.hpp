#pragma once

#include "point.h"

point::point() : _x(0), _y(0), _z(0) {}

point::point(const double x, const double y, const double z) : _x(x), _y(y), _z(z) {}

point::point(const point &_point) : point(_point._x, _point._y, _point._z) {}

point &point::operator=(const point &_point)
{
    this->_x = _point.x;
    this->_y = _point.y;
    this->_z = _point.z;

    return *this;
}

double point::get_x() const { return this->_x; }

double point::get_y() const { return this->_y; }

double point::get_z() const { return this->_z; }


void point::set_x(double x) { this->_x = x; }

void point::set_y(double y) { this->_y = y; }

void point::set_z(double z) { this->_z = z; }


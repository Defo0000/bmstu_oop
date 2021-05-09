#ifndef POINT_H
#define POINT_H

template <typename T>
class point
{
public:
    explicit point();
    explicit point(const T x, const T y, const T z);

    point(const point &_point);
    point& operator = (const point &_point);

    T get_x() const;
    T get_y() const;
    T get_z() const;

    void set_x(T x);
    void set_y(T y);
    void set_z(T z);

    void transform(const std::shared_ptr<Matrix<T>> trfm_mtr);

private:
    T _x, _y, _z;
};

#include "point.hpp:

#endif // POINT_H

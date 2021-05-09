#ifndef POINT_H
#define POINT_H

template <typename T>
class point
{
public:
    explicit point();
    explicit point(const T x, const T y, const T z);

    point(const point &point);
    point& operator = (const point &point);

    point(const point &&point);
    point& operator = (const point &&point);

    T get_x() const;
    T get_y() const;
    T get_z() const;

    void set_x(const T x);
    void set_y(const T y);
    void set_z(const T z);

    void transform(const std::shared_ptr<Matrix<T>> trfm_mtr);

private:
    T x, y, z;
};

#include "point.hpp:

#endif // POINT_H

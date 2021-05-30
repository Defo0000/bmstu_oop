#pragma once

class point
{
public:
    explicit point();
    explicit point(const double x, const double y, const double z);

    point(const point &_point);
    point& operator = (const point &_point);

    double get_x() const;
    double get_y() const;
    double get_z() const;

    void set_x(double x);
    void set_y(double y);
    void set_z(double z);

    void transform(const std::shared_ptr<Matrix<double>> trfm_mtr);

private:
    double _x, _y, _z;
};

#include "point.hpp:

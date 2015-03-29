#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

struct point
{

public:

    point(int x, int y, int z);

    static point x_unit();

    static point y_unit();

    static point z_unit();

    point operator + () const;

    point operator - () const;

public:

    int x;

    int y;

    int z;

};

bool is_unit(util::value_ref<point> p);

bool operator == (util::value_ref<point> lhs, util::value_ref<point> rhs);

bool operator != (util::value_ref<point> lhs, util::value_ref<point> rhs);

point operator + (util::value_ref<point> lhs, 
                    util::value_ref<point> rhs);

point operator - (util::value_ref<point> lhs, 
                    util::value_ref<point> rhs);

point operator * (util::value_ref<point> p, int factor);

point operator * (int factor, util::value_ref<point> p);

}
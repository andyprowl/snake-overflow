#pragma once

#include "util/value_ref.hpp"

namespace math
{

struct point3d
{

public:

    point3d(int x, int y, int z);

    static point3d x_unit();

    static point3d y_unit();

    static point3d z_unit();

    point3d operator + () const;

    point3d operator - () const;

public:

    int x;

    int y;

    int z;

};

bool is_unit(util::value_ref<point3d> p);

bool operator == (util::value_ref<point3d> lhs, util::value_ref<point3d> rhs);

bool operator != (util::value_ref<point3d> lhs, util::value_ref<point3d> rhs);

point3d operator + (util::value_ref<point3d> lhs, 
                    util::value_ref<point3d> rhs);

point3d operator - (util::value_ref<point3d> lhs, 
                    util::value_ref<point3d> rhs);

}
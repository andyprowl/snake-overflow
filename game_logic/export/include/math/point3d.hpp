#pragma once

#include "util/value_ref.hpp"

namespace math
{

struct point3d
{

public:

    point3d(int x, int y, int z);

    int x;

    int y;

    int z;

};

bool operator == (util::value_ref<point3d> lhs, util::value_ref<point3d> rhs);

bool operator != (util::value_ref<point3d> lhs, util::value_ref<point3d> rhs);


}
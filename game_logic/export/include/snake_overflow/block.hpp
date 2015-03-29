#pragma once

#include "snake_overflow/point.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{
    
struct block
{

public:

    block(util::value_ref<point> origin);

    point get_origin() const;

private:

    point origin;

};

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs);

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs);

}
#include "stdafx.hpp"

#include "snake_overflow/block.hpp"

namespace snake_overflow
{

block::block(util::value_ref<point> origin)
    : origin{origin}
{
}

point block::get_origin() const
{
    return this->origin;
}

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs)
{
    return (lhs.get_origin() == rhs.get_origin());
}

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs)
{
    return !(lhs == rhs);
}

}
#include "stdafx.hpp"

#include "snake_overflow/block.hpp"

namespace snake_overflow
{

block::block(util::value_ref<point> origin, 
             std::string texture, 
             util::value_ref<rgba_color> color,
             bool const is_solid)
    : origin{origin}
    , texture(std::move(texture))
    , color{color}
    , is_solid{is_solid}
{
}

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs)
{
    return (lhs.origin == rhs.origin);
}

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs)
{
    return !(lhs == rhs);
}

}
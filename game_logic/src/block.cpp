#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include <tuple>

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

auto tuple_from_block(util::value_ref<block> b) 
    -> decltype(std::forward_as_tuple(b.origin, b.texture, b.color, b.is_solid))
{
    return std::forward_as_tuple(b.origin, b.texture, b.color, b.is_solid);
}

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs)
{
    return (tuple_from_block(lhs) == tuple_from_block(rhs));
}

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs)
{
    return !(lhs == rhs);
}

bool is_block_visible(util::value_ref<block> b)
{
    return (b.color.alpha > 0);
}

}
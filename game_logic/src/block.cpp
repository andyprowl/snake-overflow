#include "stdafx.hpp"

#include "snake_overflow/block.hpp"

namespace snake_overflow
{

block::block(util::value_ref<point> origin, std::string texture)
    : origin{origin}
    , texture(std::move(texture))
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
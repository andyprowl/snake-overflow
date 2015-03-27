#include "stdafx.hpp"

#include "snake_overflow/game_logic/block.hpp"
#include <tuple>

namespace snake_overflow { namespace game_logic
{

block::block(int x, int y, int z)
    : x{x}
    , y{y}
    , z{z}
{
}

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs)
{
    return (std::make_tuple(lhs.x, lhs.y, lhs.z) ==
            std::make_tuple(rhs.x, rhs.y, rhs.z));
}

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs)
{
    return !(lhs == rhs);
}

} }
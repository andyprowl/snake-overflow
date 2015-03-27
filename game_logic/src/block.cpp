#include "stdafx.hpp"

#include "snake_overflow/game_logic/block.hpp"

namespace snake_overflow { namespace game_logic
{

block::block(util::value_ref<math::point3d> origin)
    : origin{origin}
{
}

math::point3d block::get_origin() const
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

} }
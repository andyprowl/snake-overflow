#include "stdafx.hpp"

#include "snake_overflow/game_logic/position.hpp"

namespace snake_overflow { namespace game_logic
{

position::position(util::value_ref<math::point3d> block_origin,
                   surface const block_surface)
    : block_origin{block_origin}
    , block_surface{block_surface}
{
}

bool operator == (util::value_ref<position> lhs, 
                  util::value_ref<position> rhs)
{
    return ((lhs.block_origin == rhs.block_origin) &&
            (lhs.block_surface == rhs.block_surface));
}

bool operator != (util::value_ref<position> lhs, 
                  util::value_ref<position> rhs)
{
    return !(lhs == rhs);
}

} }
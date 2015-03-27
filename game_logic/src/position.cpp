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

} }
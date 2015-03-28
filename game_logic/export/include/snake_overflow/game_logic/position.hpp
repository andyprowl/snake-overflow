#pragma once

#include "snake_overflow/game_logic/surface.hpp"
#include "math/point3d.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow { namespace game_logic
{

struct position
{

public:

    position(util::value_ref<math::point3d> block_origin,
             surface block_surface);

public:

    math::point3d block_origin;

    surface block_surface;

};

bool operator == (util::value_ref<position> lhs, 
                  util::value_ref<position> rhs);

bool operator != (util::value_ref<position> lhs, 
                  util::value_ref<position> rhs);

} }
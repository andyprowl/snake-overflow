#pragma once

namespace snake_overflow { namespace game_logic
{

enum class surface
{
    front,
    back,
    left,
    right,
    top,
    bottom
};

surface get_opposite_surface(surface s);

} }
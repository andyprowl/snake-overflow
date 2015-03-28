#include "stdafx.hpp"

#include "snake_overflow/game_logic/surface.hpp"
#include <cassert>

namespace snake_overflow { namespace game_logic
{

surface get_opposite_surface(surface const s)
{
    switch (s)
    {
        case surface::front: { return surface::back; }
        case surface::back: { return surface::front; }
        case surface::left: { return surface::right; }
        case surface::right: { return surface::left; }
        case surface::top: { return surface::bottom; }
        case surface::bottom: { return surface::top; }
        default: assert(false); { return surface::front; }
    }
}

} }
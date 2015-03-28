#include "stdafx.hpp"

#include "snake_overflow/game_logic/movement_profile.hpp"
#include <unordered_map>

namespace snake_overflow { namespace game_logic
{

auto const continuation_map = 
           std::unordered_map<movement_profile, movement_profile>
{
    {{surface::front, direction::positive_x()}, 
     {surface::right, direction::positive_y()}},
    {{surface::front, direction::negative_x()}, 
     {surface::left, direction::positive_y()}},
    {{surface::front, direction::positive_z()}, 
     {surface::top, direction::positive_y()}},
    {{surface::front, direction::negative_z()}, 
     {surface::bottom, direction::positive_y()}},

    {{surface::back, direction::positive_x()}, 
     {surface::right, direction::negative_y()}},
    {{surface::back, direction::negative_x()}, 
     {surface::left, direction::negative_y()}},
    {{surface::back, direction::positive_z()}, 
     {surface::top, direction::negative_y()}},
    {{surface::back, direction::negative_z()}, 
     {surface::bottom, direction::negative_y()}},

    {{surface::left, direction::positive_y()}, 
     {surface::back, direction::positive_x()}},
    {{surface::left, direction::negative_y()}, 
     {surface::front, direction::positive_x()}},
    {{surface::left, direction::positive_z()}, 
     {surface::top, direction::positive_x()}},
    {{surface::left, direction::negative_z()}, 
     {surface::bottom, direction::positive_x()}},

    {{surface::right, direction::positive_y()}, 
     {surface::back, direction::negative_x()}},
    {{surface::right, direction::negative_y()}, 
     {surface::front, direction::negative_x()}},
    {{surface::right, direction::positive_z()}, 
     {surface::top, direction::negative_x()}},
    {{surface::right, direction::negative_z()}, 
     {surface::bottom, direction::negative_x()}},

    {{surface::top, direction::positive_x()}, 
     {surface::right, direction::negative_z()}},
    {{surface::top, direction::negative_x()}, 
     {surface::left, direction::negative_z()}},
    {{surface::top, direction::positive_y()}, 
     {surface::back, direction::negative_z()}},
    {{surface::top, direction::negative_y()}, 
     {surface::front, direction::negative_z()}},

    {{surface::bottom, direction::positive_x()}, 
     {surface::right, direction::positive_z()}},
    {{surface::bottom, direction::negative_x()}, 
     {surface::left, direction::positive_z()}},
    {{surface::bottom, direction::positive_y()}, 
     {surface::back, direction::positive_z()}},
    {{surface::bottom, direction::negative_y()}, 
     {surface::front, direction::positive_z()}}
};

movement_profile::movement_profile(surface const s, direction const d)
    : block_surface{s}
    , movement_direction{d}
{
}

bool operator == (util::value_ref<movement_profile> lhs,
                  util::value_ref<movement_profile> rhs)
{
    return ((lhs.block_surface == rhs.block_surface) && 
            (lhs.movement_direction == rhs.movement_direction));
}

bool operator != (util::value_ref<movement_profile> lhs,
                  util::value_ref<movement_profile> rhs)
{
    return !(lhs == rhs);
}

movement_profile get_continuation_profile(util::value_ref<movement_profile> p)
{
    return continuation_map.at(p);
}

movement_profile get_opposite_profile(util::value_ref<movement_profile> p)
{
    return {get_opposite_surface(p.block_surface),
            get_opposite_direction(p.movement_direction)};
}

} }
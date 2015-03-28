#include "stdafx.hpp"

#include "snake_overflow/game_logic/movement_profile.hpp"
#include <unordered_map>

namespace snake_overflow { namespace game_logic
{

auto const continuation_map = 
           std::unordered_map<movement_profile, movement_profile>
{
    {{block_face::front, canonical_direction::positive_x()}, 
     {block_face::right, canonical_direction::positive_y()}},
    {{block_face::front, canonical_direction::negative_x()}, 
     {block_face::left, canonical_direction::positive_y()}},
    {{block_face::front, canonical_direction::positive_z()}, 
     {block_face::top, canonical_direction::positive_y()}},
    {{block_face::front, canonical_direction::negative_z()}, 
     {block_face::bottom, canonical_direction::positive_y()}},

    {{block_face::back, canonical_direction::positive_x()}, 
     {block_face::right, canonical_direction::negative_y()}},
    {{block_face::back, canonical_direction::negative_x()}, 
     {block_face::left, canonical_direction::negative_y()}},
    {{block_face::back, canonical_direction::positive_z()}, 
     {block_face::top, canonical_direction::negative_y()}},
    {{block_face::back, canonical_direction::negative_z()}, 
     {block_face::bottom, canonical_direction::negative_y()}},

    {{block_face::left, canonical_direction::positive_y()}, 
     {block_face::back, canonical_direction::positive_x()}},
    {{block_face::left, canonical_direction::negative_y()}, 
     {block_face::front, canonical_direction::positive_x()}},
    {{block_face::left, canonical_direction::positive_z()}, 
     {block_face::top, canonical_direction::positive_x()}},
    {{block_face::left, canonical_direction::negative_z()}, 
     {block_face::bottom, canonical_direction::positive_x()}},

    {{block_face::right, canonical_direction::positive_y()}, 
     {block_face::back, canonical_direction::negative_x()}},
    {{block_face::right, canonical_direction::negative_y()}, 
     {block_face::front, canonical_direction::negative_x()}},
    {{block_face::right, canonical_direction::positive_z()}, 
     {block_face::top, canonical_direction::negative_x()}},
    {{block_face::right, canonical_direction::negative_z()}, 
     {block_face::bottom, canonical_direction::negative_x()}},

    {{block_face::top, canonical_direction::positive_x()}, 
     {block_face::right, canonical_direction::negative_z()}},
    {{block_face::top, canonical_direction::negative_x()}, 
     {block_face::left, canonical_direction::negative_z()}},
    {{block_face::top, canonical_direction::positive_y()}, 
     {block_face::back, canonical_direction::negative_z()}},
    {{block_face::top, canonical_direction::negative_y()}, 
     {block_face::front, canonical_direction::negative_z()}},

    {{block_face::bottom, canonical_direction::positive_x()}, 
     {block_face::right, canonical_direction::positive_z()}},
    {{block_face::bottom, canonical_direction::negative_x()}, 
     {block_face::left, canonical_direction::positive_z()}},
    {{block_face::bottom, canonical_direction::positive_y()}, 
     {block_face::back, canonical_direction::positive_z()}},
    {{block_face::bottom, canonical_direction::negative_y()}, 
     {block_face::front, canonical_direction::positive_z()}}
};

auto const left_rotation_map = 
           std::unordered_map<movement_profile, canonical_direction>
{
    {{block_face::front, canonical_direction::positive_x()}, 
     canonical_direction::positive_z()},
    {{block_face::front, canonical_direction::positive_z()}, 
     canonical_direction::negative_x()},
    {{block_face::front, canonical_direction::negative_x()}, 
     canonical_direction::negative_z()},
    {{block_face::front, canonical_direction::negative_z()}, 
     canonical_direction::positive_x()},

    {{block_face::back, canonical_direction::positive_x()}, 
     canonical_direction::negative_z()},
    {{block_face::back, canonical_direction::negative_z()}, 
     canonical_direction::negative_x()},
    {{block_face::back, canonical_direction::negative_x()}, 
     canonical_direction::positive_z()},
    {{block_face::back, canonical_direction::positive_z()}, 
     canonical_direction::positive_x()},

    {{block_face::left, canonical_direction::positive_y()}, 
      canonical_direction::negative_z()},
    {{block_face::left, canonical_direction::negative_z()}, 
     canonical_direction::negative_y()},
    {{block_face::left, canonical_direction::negative_y()},
     canonical_direction::positive_z()},
    {{block_face::left, canonical_direction::positive_z()}, 
     canonical_direction::positive_y()},

    {{block_face::right, canonical_direction::positive_y()}, 
     canonical_direction::positive_z()},
    {{block_face::right, canonical_direction::positive_z()}, 
     canonical_direction::negative_y()},
    {{block_face::right, canonical_direction::negative_y()}, 
     canonical_direction::negative_z()},
    {{block_face::right, canonical_direction::negative_z()}, 
     canonical_direction::positive_y()},

    {{block_face::top, canonical_direction::positive_x()}, 
     canonical_direction::positive_y()},
    {{block_face::top, canonical_direction::positive_y()}, 
     canonical_direction::negative_x()},
    {{block_face::top, canonical_direction::negative_x()}, 
     canonical_direction::negative_y()},
    {{block_face::top, canonical_direction::negative_y()}, 
     canonical_direction::positive_x()},

    {{block_face::bottom, canonical_direction::positive_x()}, 
     canonical_direction::negative_y()},
    {{block_face::bottom, canonical_direction::negative_y()}, 
     canonical_direction::negative_x()},
    {{block_face::bottom, canonical_direction::negative_x()}, 
     canonical_direction::positive_y()},
    {{block_face::bottom, canonical_direction::positive_y()}, 
     canonical_direction::positive_x()}
};

movement_profile::movement_profile(block_face const s, 
                                   canonical_direction const d)
    : face{s}
    , direction{d}
{
}

bool operator == (util::value_ref<movement_profile> lhs,
                  util::value_ref<movement_profile> rhs)
{
    return ((lhs.face == rhs.face) && 
            (lhs.direction == rhs.direction));
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
    return {get_opposite_block_face(p.face),
            get_opposite_direction(p.direction)};
}

movement_profile get_left_turn_profile(util::value_ref<movement_profile> p)
{
    return {p.face, left_rotation_map.at(p)};
}

movement_profile get_right_turn_profile(util::value_ref<movement_profile> p)
{
    auto const opposite_block_face = get_opposite_block_face(p.face);

    auto const profile = movement_profile{opposite_block_face, 
                                          p.direction};

    return {p.face, left_rotation_map.at(profile)};
}

} }
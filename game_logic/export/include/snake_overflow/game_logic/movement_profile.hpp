#pragma once

#include "snake_overflow/game_logic/canonical_direction.hpp"
#include "snake_overflow/game_logic/block_face.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow { namespace game_logic
{

struct movement_profile
{

public:

    movement_profile(block_face s, canonical_direction d);

public:
    
    block_face face;

    canonical_direction direction;

};

bool operator == (util::value_ref<movement_profile> lhs,
                  util::value_ref<movement_profile> rhs);

bool operator != (util::value_ref<movement_profile> lhs,
                  util::value_ref<movement_profile> rhs);

movement_profile get_continuation_profile(util::value_ref<movement_profile> p);

movement_profile get_opposite_profile(util::value_ref<movement_profile> p);

movement_profile get_left_turn_profile(util::value_ref<movement_profile> p);

movement_profile get_right_turn_profile(util::value_ref<movement_profile> p);

} }

namespace std
{

template<>
struct hash<snake_overflow::game_logic::movement_profile>
{

public:

    std::size_t operator () (
        util::value_ref<snake_overflow::game_logic::movement_profile> p)
    {
        auto const s = p.face;
        auto const dir = p.direction;

        return (std::hash<std::size_t>{}(static_cast<std::size_t>(s)) ^
                std::hash<snake_overflow::game_logic::canonical_direction>{}(dir));
    }

};

}
#include "stdafx.hpp"

#include "snake_overflow/game_logic/direction.hpp"
#include "snake_overflow/game_logic/dynamics.hpp"
#include "snake_overflow/game_logic/movement_profile.hpp"
#include "snake_overflow/game_logic/point3d.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/territory.hpp"
#include "util/contains.hpp"
#include <algorithm>

namespace snake_overflow { namespace game_logic
{

std::vector<block> territory::get_blocks() const
{
    return this->blocks;
}

void territory::add_block(util::value_ref<block> b)
{
    if (util::contains(this->blocks, b))
    {
        return;
    }

    this->blocks.push_back(b);
}

dynamics territory::compute_step(util::value_ref<dynamics> d) const
{
    auto turn_dynamics = compute_hypothetical_turn_to_adjacent_block(d);

    if (contains_block(turn_dynamics.pos.block_origin))
    {
        return turn_dynamics;
    }
    
    auto const inertial_target = position{d.pos.block_origin + 
                                          get_direction_vector(d.dir), 
                                          d.pos.block_surface};

    if (contains_block(inertial_target.block_origin))
    {
        return {inertial_target, d.dir};
    }
    else
    {
        return compute_fallback_turn_on_same_block(d);
    }
}

dynamics territory::compute_hypothetical_turn_to_adjacent_block(
    util::value_ref<dynamics> d) const
{
    auto const fallback = get_continuation_profile({d.pos.block_surface, 
                                                    d.dir});

    auto const opp_fallback = get_opposite_profile(fallback);

    auto const block_origin = 
        d.pos.block_origin +
        get_direction_vector(opp_fallback.movement_direction) + 
        get_direction_vector(d.dir);

    return {{block_origin, opp_fallback.block_surface}, 
            opp_fallback.movement_direction};
}

dynamics territory::compute_fallback_turn_on_same_block(
    util::value_ref<dynamics> d) const
{
    auto const fallback = get_continuation_profile({d.pos.block_surface, 
                                                    d.dir});

    return {{d.pos.block_origin, fallback.block_surface},
            fallback.movement_direction};
}

bool territory::contains_block(util::value_ref<point3d> p) const
{
    auto const it = std::find_if(std::cbegin(this->blocks),
                                 std::cend(this->blocks),
                                 [&p] (util::value_ref<block> b)
    {
        return (b.get_origin() == p);
    });

    return (it != std::cend(this->blocks));
}

} }
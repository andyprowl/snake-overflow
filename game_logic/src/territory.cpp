#include "stdafx.hpp"

#include "snake_overflow/canonical_direction.hpp"
#include "snake_overflow/dynamics.hpp"
#include "snake_overflow/movement_profile.hpp"
#include "snake_overflow/point.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/territory.hpp"
#include "util/contains.hpp"
#include <algorithm>

namespace snake_overflow
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

    if (contains_block(turn_dynamics.location))
    {
        return turn_dynamics;
    }
    
    auto const inertial_target = position{
        d.location + get_direction_vector(d.profile.direction), 
        d.profile.face};

    if (contains_block(inertial_target.location))
    {
        return {inertial_target.location, d.profile};
    }
    else
    {
        return compute_fallback_turn_on_same_block(d);
    }
}

dynamics territory::compute_hypothetical_turn_to_adjacent_block(
    util::value_ref<dynamics> d) const
{
    auto const fallback = get_continuation_profile(d.profile);

    auto const opp_fallback = get_opposite_profile(fallback);

    auto const location = 
        d.location +
        get_direction_vector(opp_fallback.direction) + 
        get_direction_vector(d.profile.direction);

    return {location, opp_fallback};
}

dynamics territory::compute_fallback_turn_on_same_block(
    util::value_ref<dynamics> d) const
{
    auto const fallback = get_continuation_profile(d.profile);

    return {d.location, fallback};
}

bool territory::contains_block(util::value_ref<point> p) const
{
    auto const it = std::find_if(std::cbegin(this->blocks),
                                 std::cend(this->blocks),
                                 [&p] (util::value_ref<block> b)
    {
        return (b.get_origin() == p);
    });

    return (it != std::cend(this->blocks));
}

}
#include "stdafx.hpp"

#include "snake_overflow/canonical_direction.hpp"
#include "snake_overflow/footprint.hpp"
#include "snake_overflow/movement_profile.hpp"
#include "snake_overflow/point.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/terrain.hpp"
#include "util/contains.hpp"
#include <algorithm>

namespace snake_overflow
{

util::value_ref<std::vector<block>> terrain::get_blocks() const
{
    return this->blocks;
}

void terrain::add_block(util::value_ref<block> b)
{
    if (contains_block(b.origin))
    {
        return;
    }

    this->blocks.push_back(b);
}

void terrain::remove_block(util::value_ref<point> origin)
{
    auto const it = find_block(origin);
    if (it == std::cend(this->blocks))
    {
        return;
    }

    this->blocks.erase(it);
}

bool terrain::contains_block(util::value_ref<point> p) const
{
    auto const it = find_block(p);

    return (it != std::cend(this->blocks));
}

bool terrain::contains_solid_block(util::value_ref<point> p) const
{
    auto const it = find_block(p);

    if (it == std::cend(this->blocks))
    {
        return false;
    }

    return it->is_solid;
}

block terrain::get_block(util::value_ref<point> origin) const
{
    auto const it = find_block(origin);
    if (it == std::cend(this->blocks))
    {
        throw block_not_found_exception{};
    }

    return *it;
}

footprint terrain::compute_next_footprint(util::value_ref<footprint> d) const
{
    auto turn_footprint = compute_hypothetical_turn_to_adjacent_block(d);

    if (contains_solid_block(turn_footprint.location))
    {
        return turn_footprint;
    }
    
    auto const inertial_target = position{
        d.location + get_direction_vector(d.profile.direction), 
        d.profile.face};

    if (contains_solid_block(inertial_target.location))
    {
        return {inertial_target.location, d.profile};
    }
    else
    {
        return compute_fallback_turn_on_same_block(d);
    }
}

footprint terrain::compute_hypothetical_turn_to_adjacent_block(
    util::value_ref<footprint> d) const
{
    auto const fallback = get_continuation_profile(d.profile);

    auto const opp_fallback = get_opposite_profile(fallback);

    auto const location = 
        d.location +
        get_direction_vector(opp_fallback.direction) + 
        get_direction_vector(d.profile.direction);

    return {location, opp_fallback};
}

footprint terrain::compute_fallback_turn_on_same_block(
    util::value_ref<footprint> d) const
{
    auto const fallback = get_continuation_profile(d.profile);

    return {d.location, fallback};
}

std::vector<block>::const_iterator terrain::find_block(
    util::value_ref<point> p) const
{
    return std::find_if(std::cbegin(this->blocks),
                        std::cend(this->blocks),
                        [&p] (util::value_ref<block> b)
    {
        return (b.origin == p);
    });
}

}
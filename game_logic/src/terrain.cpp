#include "stdafx.hpp"

#include "snake_overflow/canonical_direction.hpp"
#include "snake_overflow/footprint.hpp"
#include "snake_overflow/item.hpp"
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

    if (!it->items.empty())
    {
        throw block_not_empty_exception{};
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

void terrain::add_item(std::unique_ptr<item>&& i)
{
    auto const pos = i->get_position();

    auto it = find_block(pos.location);
    if (it == std::cend(this->blocks))
    {
        throw block_not_found_exception{};
    }

    throw_if_block_face_is_occupied(*it, pos.face);

    it->items.push_back(i.get());

    this->items.push_back(std::move(i));
}

std::unique_ptr<item> terrain::remove_item(util::value_ref<item> i)
{
    remove_item_from_placement_block(i);

    return release_item_ownership(i);
}

int terrain::get_num_of_items() const
{
    return static_cast<int>(this->items.size());
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

void terrain::throw_if_block_face_is_occupied(util::value_ref<block> b, 
                                              block_face face) const
{
    auto it = std::find_if(std::cbegin(b.items), 
                           std::cend(b.items),
                           [face] (item const* const i)
    {
        return (i->get_position().face == face);
    });

    if (it != std::cend(b.items))
    {
        throw position_not_free_exception{};
    }
}

void terrain::remove_item_from_placement_block(util::value_ref<item> i)
{
    auto const pos = i.get_position();

    auto const it = find_block(pos.location);
    
    auto const block_item_it = std::find(std::cbegin(it->items), 
                                         std::cend(it->items), 
                                         &i);

    if (block_item_it == std::cend(it->items))
    {
        throw item_not_found_exception{};
    }

    it->items.erase(block_item_it);
}

std::unique_ptr<item> terrain::release_item_ownership(util::value_ref<item> i)
{
    auto const item_it = std::find_if(std::begin(this->items),
                                      std::end(this->items),
                                      [&i] (std::unique_ptr<item> const& p)
    {
        return (p.get() == &i);
    });

    auto owned_item = std::move(*item_it);

    this->items.erase(item_it);

    return owned_item;
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

std::vector<block>::iterator terrain::find_block(
    util::value_ref<point> p)
{
    return std::find_if(std::begin(this->blocks),
                        std::end(this->blocks),
                        [&p] (util::value_ref<block> b)
    {
        return (b.origin == p);
    });
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
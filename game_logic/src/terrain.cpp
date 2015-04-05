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
#include <iterator>
#include <vector>

namespace snake_overflow
{

std::unique_ptr<terrain> terrain::clone() const
{
    auto t = std::make_unique<terrain>();

    for_each_block([&t] (block b) // Notice: we make a copy!
    {
        b.items.clear();

        t->add_block(b);
    });

    return t;
}

void terrain::add_block(util::value_ref<block> b)
{
    if (contains_block(b.origin))
    {
        return;
    }

    auto result = this->block_index.emplace(b.origin, b);

    this->blocks.push_back(&(result.first->second));
}

void terrain::remove_block(util::value_ref<point> origin)
{
    auto const it = this->block_index.find(origin);
    if (it == std::cend(this->block_index))
    {
        return;
    }

    if (!it->second.items.empty()) { throw block_not_empty_exception{}; }

    auto const vector_it = std::remove(std::begin(this->blocks), 
                                       std::end(this->blocks), 
                                       &it->second);

    this->blocks.erase(vector_it, std::cend(this->blocks));

    this->block_index.erase(origin);
}

bool terrain::contains_block(util::value_ref<point> p) const
{
    auto const it = this->block_index.find(p);
    
    return (it != std::cend(this->block_index));
}

bool terrain::contains_solid_block(util::value_ref<point> p) const
{
    auto const it = this->block_index.find(p);

    if (it == std::cend(this->block_index))
    {
        return false;
    }

    return it->second.is_solid;
}

block terrain::get_block(util::value_ref<point> origin) const
{
    auto const it = this->block_index.find(origin);

    if (it == std::cend(this->block_index))
    {
        throw block_not_found_exception{};
    }

    return it->second;
}

std::vector<block> terrain::get_all_blocks() const
{
    auto v = std::vector<block>{};

    std::transform(std::begin(this->blocks),
                   std::end(this->blocks),
                   std::back_inserter(v),
                   [] (block const* const b)
    {
        return *b;
    });

    return v;
}

void terrain::add_item(std::unique_ptr<item>&& i)
{
    auto const pos = i->get_position();

    auto it = this->block_index.find(pos.location);
    if (it == std::cend(this->block_index))
    {
        throw block_not_found_exception{};
    }

    throw_if_position_is_not_viable(pos);

    it->second.items.push_back(i.get());

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

std::vector<position> terrain::get_all_free_item_positions() const
{
    auto valid_positions = std::vector<position>{};

    for (auto const b : this->blocks)
    {
        gather_all_free_item_positions_on_block(*b, valid_positions);
    }

    return valid_positions;
}

footprint terrain::compute_next_footprint(util::value_ref<footprint> f) const
{
    auto turn_footprint = compute_hypothetical_turn_to_adjacent_block(f);

    if (contains_solid_block(turn_footprint.location))
    {
        return turn_footprint;
    }
    
    auto const inertial_target = position{
        f.location + get_direction_vector(f.profile.direction), 
        f.profile.face};

    if (contains_solid_block(inertial_target.location))
    {
        return {inertial_target.location, f.profile};
    }
    else
    {
        return compute_fallback_turn_on_same_block(f);
    }
}

void terrain::finalize_for_rendering()
{
    make_occluded_blocks_transparent();

    sort_for_rendering_with_alpha_blending();
}

void terrain::throw_if_position_is_not_viable(
    util::value_ref<position> pos) const
{
    auto const viable = can_place_item_at_position(pos, *this);

    if (!(viable))
    {
        throw bad_item_position_exception{};
    }
}

void terrain::remove_item_from_placement_block(util::value_ref<item> i)
{
    auto const pos = i.get_position();

    auto const it = this->block_index.find(pos.location);
    
    auto const block_item_it = std::find(std::cbegin(it->second.items), 
                                         std::cend(it->second.items), 
                                         &i);

    if (block_item_it == std::cend(it->second.items))
    {
        throw item_not_found_exception{};
    }

    it->second.items.erase(block_item_it);
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

void terrain::gather_all_free_item_positions_on_block(
    util::value_ref<block> b, 
    std::vector<position>& positions) const
{
    gather_item_position_if_free({b.origin, block_face::front}, positions);

    gather_item_position_if_free({b.origin, block_face::back}, positions);

    gather_item_position_if_free({b.origin, block_face::left}, positions);

    gather_item_position_if_free({b.origin, block_face::right}, positions);

    gather_item_position_if_free({b.origin, block_face::top}, positions);

    gather_item_position_if_free({b.origin, block_face::bottom}, positions);
}

void terrain::gather_item_position_if_free(
    util::value_ref<position> pos,
    std::vector<position>& positions) const
{
    if (can_place_item_at_position(pos, *this))
    {
        positions.push_back(pos);
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

void terrain::sort_for_rendering_with_alpha_blending()
{
    std::stable_sort(std::begin(this->blocks), 
                     std::end(this->blocks),
                     [] (block const* const b1, block const* const b2)
    {
        if (b1->color.alpha == b2->color.alpha)
        {
            return (b1->origin < b2->origin);
        }
        else
        {
            return (b1->color.alpha > b2->color.alpha);
        }
    });
}

void terrain::make_occluded_blocks_transparent()
{
    auto occluded_blocks = std::vector<block*>{};

    std::copy_if(std::cbegin(this->blocks),
                 std::cend(this->blocks),
                 std::back_inserter(occluded_blocks),
                 [this] (block const* const b)
    {
        return has_only_non_transparent_neighbors(b->origin);
    });

    for (auto const b : occluded_blocks)
    {
        b->color.alpha = 0;
    }
}

bool terrain::has_only_non_transparent_neighbors(
    util::value_ref<point> location) const
{
    return (contains_non_transparent_block(location + point::x_unit()) &&
            contains_non_transparent_block(location - point::x_unit()) &&
            contains_non_transparent_block(location + point::y_unit()) &&
            contains_non_transparent_block(location - point::y_unit()) &&
            contains_non_transparent_block(location + point::z_unit()) &&
            contains_non_transparent_block(location - point::z_unit()));
}

bool terrain::contains_non_transparent_block(util::value_ref<point> p) const
{
    auto const it = this->block_index.find(p);

    if (it == std::cend(this->block_index))
    {
        return false;
    }

    return (it->second.color.alpha == 255);
}

bool is_position_free_of_items(util::value_ref<position> pos, terrain const& t)
{
    auto const b = t.get_block(pos.location);

    auto it = std::find_if(std::cbegin(b.items), 
                           std::cend(b.items),
                           [&pos] (item const* const i)
    {
        return (i->get_position().face == pos.face);
    });

    return (it == std::cend(b.items));
}

bool is_position_walkable(util::value_ref<position> pos, terrain const& t)
{
    auto const is_solid = t.contains_solid_block(pos.location);
    if (!is_solid)
    {
        return false;
    }

    auto const n = get_face_normal(pos.face);

    auto const adjacent_origin = pos.location + n;

    auto const has_solid_neighbor = t.contains_solid_block(adjacent_origin);

    return !(has_solid_neighbor);
}

bool can_place_item_at_position(util::value_ref<position> pos, 
                                terrain const& t)
{
    return (is_position_walkable(pos, t) && is_position_free_of_items(pos, t));
}

item* find_item(util::value_ref<position> pos, terrain const& t)
{
    auto const b = t.get_block(pos.location);

    auto const it = std::find_if(std::cbegin(b.items), 
                                 std::cend(b.items),
                                 [&pos] (item const* const i)
    {
        return (i->get_position().face == pos.face);
    });

    return (it != std::cend(b.items)) ? *it : nullptr;
}

}
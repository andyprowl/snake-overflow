#pragma once

#include "snake_overflow/block.hpp"
#include "snake_overflow/item.hpp"
#include "util/noexcept.hpp"
#include "util/value_ref.hpp"
#include <memory>
#include <vector>

namespace snake_overflow
{

enum class block_face;

struct block;
struct canonical_direction;
struct footprint;
struct point;

class block_not_empty_exception : public virtual std::exception
{
};

class block_not_found_exception : public virtual std::exception
{
};

class item_not_found_exception : public virtual std::exception
{
};

class position_not_free_exception : public virtual std::exception
{
};

class terrain
{

public:
    
    util::value_ref<std::vector<block>> get_blocks() const;

    void add_block(util::value_ref<block> b);

    void remove_block(util::value_ref<point> origin);

    bool contains_block(util::value_ref<point> p) const;

    bool contains_solid_block(util::value_ref<point> p) const;

    block get_block(util::value_ref<point> origin) const;

    void add_item(std::unique_ptr<item>&& i);

    std::unique_ptr<item> remove_item(util::value_ref<item> i);

    int get_num_of_items() const;

    footprint compute_next_footprint(util::value_ref<footprint> d) const;

private:

    void throw_if_block_face_is_occupied(util::value_ref<block> b, 
                                         block_face face) const;

    void remove_item_from_placement_block(util::value_ref<item> i);

    std::unique_ptr<item> release_item_ownership(util::value_ref<item> i);

    footprint compute_hypothetical_turn_to_adjacent_block(
        util::value_ref<footprint> d) const;

    footprint compute_fallback_turn_on_same_block(
        util::value_ref<footprint> d) const;

    std::vector<block>::iterator find_block(
        util::value_ref<point> p);

    std::vector<block>::const_iterator find_block(
        util::value_ref<point> p) const;

private:

    std::vector<block> blocks;

    std::vector<std::unique_ptr<item>> items;

};

bool is_position_occupied(util::value_ref<position> pos, terrain const& t);

}
#pragma once

#include "snake_overflow/block.hpp"
#include "snake_overflow/item.hpp"
#include "util/noexcept.hpp"
#include "util/value_ref.hpp"
#include <boost/optional.hpp>
#include <memory>
#include <unordered_map>
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

class bad_item_position_exception : public virtual std::exception
{
};

class terrain
{

public:
    
    template<typename F>
    void for_each_block(F&& f) const
    {
        for (auto const b : this->blocks)
        {
            (std::forward<F>(f))(*b);
        }
    }

    template<typename F>
    void for_each_item(F&& f) const
    {
        for (auto const& i : this->items)
        {
            (std::forward<F>(f))(*i);
        }
    }

    std::unique_ptr<terrain> clone() const;

    void add_block(util::value_ref<block> b);

    void remove_block(util::value_ref<point> origin);

    bool contains_block(util::value_ref<point> p) const;

    bool contains_solid_block(util::value_ref<point> p) const;

    block get_block(util::value_ref<point> origin) const;

    std::vector<block> get_all_blocks() const;

    void sort_for_rendering();

    void add_item(std::unique_ptr<item>&& i);

    std::unique_ptr<item> remove_item(util::value_ref<item> i);

    int get_num_of_items() const;

    std::vector<position> get_all_free_item_positions() const;

    footprint compute_next_footprint(util::value_ref<footprint> d) const;

private:

    void throw_if_position_is_not_viable(util::value_ref<position> pos) const;

    void remove_item_from_placement_block(util::value_ref<item> i);

    std::unique_ptr<item> release_item_ownership(util::value_ref<item> i);

    void gather_all_free_item_positions_on_block(
        util::value_ref<block> b, 
        std::vector<position>& positions) const;

    void gather_item_position_if_free(util::value_ref<position> pos,
                                      std::vector<position>& positions) const;

    footprint compute_hypothetical_turn_to_adjacent_block(
        util::value_ref<footprint> d) const;

    footprint compute_fallback_turn_on_same_block(
        util::value_ref<footprint> d) const;

private:
    
    std::unordered_map<point, block> block_index;

    // The redundant `blocks` collection is required in order to keep 
    // ordering information and allow fast iteration. The ordering is relevant
    // for rendering when blocks with transparent color are present.
    // The for_each_block() function uses this collection to perform iteration,
    // which makes it possible to draw blocks in a sensible order.
    std::vector<block*> blocks;

    std::vector<std::unique_ptr<item>> items;

};

bool is_position_free_of_items(util::value_ref<position> pos, terrain const& t);

bool is_position_walkable(util::value_ref<position> pos, terrain const& t);

bool can_place_item_at_position(util::value_ref<position> pos, 
                                terrain const& t);

item* find_item(util::value_ref<position> pos, terrain const& t);

}
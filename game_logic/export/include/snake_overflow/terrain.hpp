#pragma once

#include "snake_overflow/block.hpp"
#include "util/noexcept.hpp"
#include "util/value_ref.hpp"
#include <vector>

namespace snake_overflow
{

struct block;
struct canonical_direction;
struct footprint;
struct point;

class block_not_found_exception : public virtual std::exception
{
};

class terrain
{

public:
    
    util::value_ref<std::vector<block>> get_blocks() const;

    void add_block(util::value_ref<block> b);

    void remove_block(util::value_ref<point> origin);

    block get_block(util::value_ref<point> origin) const;

    footprint compute_next_footprint(util::value_ref<footprint> d) const;

private:

    footprint compute_hypothetical_turn_to_adjacent_block(
        util::value_ref<footprint> d) const;

    footprint compute_fallback_turn_on_same_block(
        util::value_ref<footprint> d) const;

    bool contains_solid_block(util::value_ref<point> p) const;

    bool contains_block(util::value_ref<point> p) const;

    std::vector<block>::const_iterator find_block(
        util::value_ref<point> p) const;

private:

    std::vector<block> blocks;

};

}
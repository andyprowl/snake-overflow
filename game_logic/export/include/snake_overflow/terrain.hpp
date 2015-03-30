#pragma once

#include "snake_overflow/block.hpp"
#include "util/noexcept.hpp"
#include "util/value_ref.hpp"
#include <vector>

namespace snake_overflow
{

struct block;
struct canonical_direction;
struct dynamics;
struct point;

class terrain
{

public:
    
    util::value_ref<std::vector<block>> get_blocks() const;

    void add_block(util::value_ref<block> b);

    void remove_block(util::value_ref<point> origin);

    dynamics compute_step(util::value_ref<dynamics> d) const;

private:

    dynamics compute_hypothetical_turn_to_adjacent_block(
        util::value_ref<dynamics> d) const;

    dynamics compute_fallback_turn_on_same_block(
        util::value_ref<dynamics> d) const;

    bool contains_solid_block(util::value_ref<point> p) const;

    bool contains_block(util::value_ref<point> p) const;

    std::vector<block>::const_iterator find_block(
        util::value_ref<point> p) const;

private:

    std::vector<block> blocks;

};

}
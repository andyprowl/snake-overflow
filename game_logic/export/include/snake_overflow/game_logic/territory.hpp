#pragma once

#include "snake_overflow/game_logic/block.hpp"
#include "util/noexcept.hpp"
#include "util/value_ref.hpp"
#include <vector>

namespace snake_overflow { namespace game_logic
{

struct block;
struct direction;
struct dynamics;
struct point3d;

class territory
{

public:
    
    std::vector<block> get_blocks() const;

    void add_block(util::value_ref<block> b);

    dynamics compute_step(util::value_ref<dynamics> d) const;

private:

    dynamics compute_hypothetical_turn_to_adjacent_block(
        util::value_ref<dynamics> d) const;

    dynamics compute_fallback_turn_on_same_block(
        util::value_ref<dynamics> d) const;

    bool contains_block(util::value_ref<point3d> p) const;

private:

    std::vector<block> blocks;

};

} }
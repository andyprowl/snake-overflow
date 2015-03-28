#include "stdafx.hpp"

#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/territory.hpp"
#include "math/point3d.hpp"
#include "util/contains.hpp"

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

position territory::compute_step_target(util::value_ref<position> start,
                                        util::value_ref<math::point3d> dir) const
{
    return {start.block_origin + dir, start.block_surface};
}


} }
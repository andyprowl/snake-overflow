#include "stdafx.hpp"

#include "snake_overflow/game_logic/direction.hpp"
#include "snake_overflow/game_logic/dynamics.hpp"
#include "snake_overflow/game_logic/point3d.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/territory.hpp"
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

dynamics territory::compute_step(util::value_ref<dynamics> d) const
{
    auto const v = get_direction_vector(d.dir);

    return {{d.pos.block_origin + v, d.pos.block_surface}, d.dir};
}


} }
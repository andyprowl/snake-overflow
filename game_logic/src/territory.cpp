#include "stdafx.hpp"

#include "snake_overflow/game_logic/territory.hpp"
#include "snake_overflow/game_logic/block.hpp"

namespace snake_overflow { namespace game_logic
{

std::vector<block> territory::get_blocks() const
{
    return this->blocks;
}

void territory::add_block(util::value_ref<block> b)
{
    this->blocks.push_back(b);
}

} }
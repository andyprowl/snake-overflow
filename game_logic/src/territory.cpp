#include "stdafx.hpp"

#include "snake_overflow/game_logic/territory.hpp"
#include "snake_overflow/game_logic/block.hpp"

namespace snake_overflow { namespace game_logic
{

territory::territory()
{
    this->blocks.push_back({0, 0, 0});
}

std::vector<block> territory::get_blocks() const
{
    return this->blocks;
}

} }
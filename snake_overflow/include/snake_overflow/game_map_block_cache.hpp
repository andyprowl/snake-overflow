#pragma once

#include "snake_overflow/block.hpp"
#include <unordered_map>
#include <vector>

namespace snake_overflow
{

class game_map;

class game_map_block_cache
{

public:

    std::vector<block> get_map_blocks(game_map const& m) const;

    void cache_map_blocks(game_map const& m) const;

private:

    void sort_blocks_for_rendering(std::vector<block>& blocks) const;

private:

    mutable std::unordered_map<std::string, std::vector<block>> block_map;

};

}
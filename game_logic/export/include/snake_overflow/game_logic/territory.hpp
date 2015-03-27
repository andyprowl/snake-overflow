#pragma once

#include <vector>

namespace snake_overflow { namespace game_logic
{

struct block;

class territory
{

public:

    territory();

    std::vector<block> get_blocks() const;

private:

    std::vector<block> blocks;

};

} }
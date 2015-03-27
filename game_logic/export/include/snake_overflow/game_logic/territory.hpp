#pragma once

#include "util/value_ref.hpp"
#include <vector>

namespace snake_overflow { namespace game_logic
{

struct block;

class territory
{

public:
    
    std::vector<block> get_blocks() const;

    void add_block(util::value_ref<block> b);

private:

    std::vector<block> blocks;

};

} }
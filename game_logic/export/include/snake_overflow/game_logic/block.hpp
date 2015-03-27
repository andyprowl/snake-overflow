#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow { namespace game_logic
{
    
struct block
{

public:

    block(int x, int y, int z);

    int x;

    int y;

    int z;

};

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs);

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs);

} }
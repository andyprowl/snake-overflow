#pragma once

#include "snake_overflow/game_logic/point.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow { namespace game_logic
{
    
struct block
{

public:

    block(util::value_ref<point> origin);

    point get_origin() const;

private:

    point origin;

};

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs);

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs);

} }
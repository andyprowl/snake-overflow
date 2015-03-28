#pragma once

#include "snake_overflow/game_logic/point3d.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow { namespace game_logic
{
    
struct block
{

public:

    block(util::value_ref<point3d> origin);

    point3d get_origin() const;

private:

    point3d origin;

};

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs);

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs);

} }
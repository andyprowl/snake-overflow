#include "stdafx.hpp"

#include "snake_overflow/game_logic/dynamics.hpp"

namespace snake_overflow { namespace game_logic
{

dynamics::dynamics(util::value_ref<position> pos, 
                   util::value_ref<direction> dir)
    : pos{pos}
    , dir{dir}
{
}

bool operator == (util::value_ref<dynamics> lhs, util::value_ref<dynamics> rhs)
{
    return ((lhs.pos == rhs.pos) && (lhs.dir == rhs.dir));
}

bool operator != (util::value_ref<dynamics> lhs, util::value_ref<dynamics> rhs)
{
    return !(lhs == rhs);
}

} }
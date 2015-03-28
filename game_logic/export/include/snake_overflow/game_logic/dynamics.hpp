#pragma once

#include "snake_overflow/game_logic/direction.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow { namespace game_logic
{

struct position;
struct direction;

struct dynamics
{

public:

    dynamics(util::value_ref<position> pos, util::value_ref<direction> dir);

public:

    position pos;

    direction dir;

};

bool operator == (util::value_ref<dynamics> lhs, util::value_ref<dynamics> rhs);

bool operator != (util::value_ref<dynamics> lhs, util::value_ref<dynamics> rhs);

} }
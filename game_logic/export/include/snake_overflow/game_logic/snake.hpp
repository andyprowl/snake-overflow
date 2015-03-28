#pragma once

#include "snake_overflow/game_logic/position.hpp"
#include "util/value_ref.hpp"
#include <vector>

namespace snake_overflow { namespace game_logic
{

struct direction;
struct dynamics;
struct position;

class territory;

class snake
{

public:

    snake(territory& habitat, 
          util::value_ref<dynamics> initial_dynamics, 
          int initial_length);

    std::vector<position> get_body() const;

private:

    territory& habitat;

    std::vector<position> body;

};

} }
#pragma once

#include "snake_overflow/game_logic/direction.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "util/value_ref.hpp"
#include <vector>

namespace snake_overflow { namespace game_logic
{

struct position;

class territory;

class snake
{

public:

    snake(territory& habitat, 
          util::value_ref<position> start_position, 
          int initial_length,
          direction initial_direction);

    std::vector<position> get_body() const;

private:

    territory& habitat;

    std::vector<position> body;

};

} }
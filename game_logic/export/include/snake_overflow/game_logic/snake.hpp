#pragma once

#include "snake_overflow/game_logic/dynamics.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "util/value_ref.hpp"
#include <deque>
#include <vector>

namespace snake_overflow { namespace game_logic
{

struct direction;
struct position;

class territory;

class snake
{

public:

    snake(territory& habitat, 
          util::value_ref<dynamics> initial_dynamics, 
          int initial_length);

    std::vector<position> get_body() const;

    direction get_direction() const;

    void advance();

    void grow(int size);

private:

    territory& habitat;

    std::deque<position> body;

    dynamics current_dynamics;

    int growth;

};

} }
#pragma once

#include "snake_overflow/dynamics.hpp"
#include "snake_overflow/position.hpp"
#include "util/value_ref.hpp"
#include <deque>
#include <vector>

namespace snake_overflow
{

struct canonical_direction;
struct position;

class territory;

class snake
{

public:

    snake(territory& habitat, 
          util::value_ref<dynamics> initial_dynamics, 
          int initial_length);

    std::vector<position> get_body() const;

    canonical_direction get_direction() const;

    void advance();

    void grow(int size);

    void turn_left();

    void turn_right();

private:

    territory& habitat;

    std::deque<position> body;

    dynamics current_dynamics;

    int growth;

};

}
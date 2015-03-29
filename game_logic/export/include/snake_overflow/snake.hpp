#pragma once

#include "snake_overflow/dynamics.hpp"
#include "util/value_ref.hpp"
#include <deque>
#include <vector>

namespace snake_overflow
{

struct canonical_direction;

class territory;

class snake
{

public:

    snake(territory& habitat, 
          util::value_ref<dynamics> initial_dynamics, 
          int initial_length);

    std::vector<dynamics> get_trail() const;

    canonical_direction get_direction() const;

    canonical_direction get_trail_direction(int part_index) const;

    int get_length() const;

    void advance();

    void grow(int size);

    void turn_left();

    void turn_right();

private:

    territory& habitat;

    std::deque<dynamics> body;

    dynamics current_dynamics;

    int growth;

};

}
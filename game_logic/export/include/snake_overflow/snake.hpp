#pragma once

#include "snake_overflow/dynamics.hpp"
#include "util/value_ref.hpp"
#include <deque>
#include <vector>

namespace snake_overflow
{

struct canonical_direction;

class terrain;

class snake
{

public:

    snake(terrain const& habitat, 
          util::value_ref<footprint> initial_footprint, 
          int initial_length);

    std::vector<dynamics> get_trail() const;

    dynamics get_trail_head() const;

    canonical_direction get_direction() const;

    canonical_direction get_trail_direction(int part_index) const;

    int get_length() const;

    void advance();

    void grow(int size);

    void turn_left();

    void turn_right();

private:

    terrain const& habitat;

    std::deque<dynamics> trail;

    dynamics current_dynamics;

    int growth;

};

}
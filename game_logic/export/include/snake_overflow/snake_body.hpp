#pragma once

#include "snake_overflow/dynamics.hpp"
#include "util/value_ref.hpp"
#include <boost/signals2/signal.hpp>
#include <deque>
#include <vector>

namespace snake_overflow
{

struct canonical_direction;

class terrain;

class snake_body
{

public:

    using movement_event_handler = 
          std::function<void(util::value_ref<footprint>)>;

public:

    snake_body(terrain& habitat, 
               util::value_ref<footprint> initial_footprint, 
               int initial_length);

    terrain& get_terrain() const;

    std::vector<dynamics> get_trail() const;

    dynamics get_trail_head() const;

    canonical_direction get_direction() const;
    
    bool is_position_in_tail(util::value_ref<position> pos) const;

    int get_length() const;

    void advance();

    void grow(int size);

    void shrink(int size);

    void turn_left();

    void turn_right();

    boost::signals2::connection register_movement_handler(
        movement_event_handler handler) const;

private:

    using movement_event = 
          boost::signals2::signal<void(util::value_ref<footprint>)>;

private:

    void grow_or_cut_last_tail_part();

private:

    terrain& habitat;

    std::deque<dynamics> trail;

    dynamics current_dynamics;

    int cells_to_grow;

    int cells_to_shrink;

    mutable movement_event on_movement;

};

}
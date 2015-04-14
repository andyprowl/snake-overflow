#pragma once

#include "util/value_ref.hpp"
#include <boost/signals2/connection.hpp>
#include <boost/signals2/signal.hpp>

namespace snake_overflow
{

struct position;

class dead_snake_flag;
class item;
class snake;
class terrain;

class collision_handler
{

public:

    using item_picked_event_handler = std::function<void(item&)>;

public:

    collision_handler(snake& hero, dead_snake_flag& dead_flag);

    boost::signals2::connection register_item_picked_event_handler(
        item_picked_event_handler h);

private:

    void register_snake_movement_handler();

    void on_snake_movement(snake& hero, util::value_ref<position> pos) const;

    void handle_item_collision(snake& hero, 
                               util::value_ref<position> pos) const;

    void handle_self_collision(snake& hero, 
                               util::value_ref<position> pos) const;

private:

    snake& hero;
    
    dead_snake_flag& dead_flag;

    boost::signals2::signal<void(item&)> on_item_picked;

    boost::signals2::scoped_connection on_movement_connection;

};

}
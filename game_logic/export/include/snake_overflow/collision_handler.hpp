#pragma once

#include "util/value_ref.hpp"
#include <boost/signals2/connection.hpp>

namespace snake_overflow
{

struct position;

class dead_snake_flag;
class snake;
class terrain;

class collision_handler
{

public:

    collision_handler(snake& hero, dead_snake_flag& dead_flag);

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

    boost::signals2::scoped_connection on_movement_connection;

};

}
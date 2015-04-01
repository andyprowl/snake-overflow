#pragma once

#include "util/value_ref.hpp"
#include <boost/signals2/connection.hpp>

namespace snake_overflow
{

struct position;

class game;
class snake;
class terrain;

class collision_handler
{

public:

    collision_handler(game& g);

private:

    void register_snake_movement_handler();

    void on_snake_movement(snake& s, util::value_ref<position> pos) const;

    void handle_item_collision(snake& s, util::value_ref<position> pos) const;

    void handle_self_collision(snake& s, util::value_ref<position> pos) const;

private:

    game& parent_game;

    terrain& ground;

    boost::signals2::scoped_connection on_movement_connection;

};

}
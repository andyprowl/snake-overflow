#pragma once

#include "snake_overflow/collision_handler.hpp"
#include "snake_overflow/dead_snake_flag.hpp"
#include "snake_overflow/snake_boolean_parameter.hpp"
#include "snake_overflow/snake_integer_parameter.hpp"
#include "snake_overflow/snake_body.hpp"
#include <memory>

namespace snake_overflow
{

class terrain;

class snake
{

public:

    snake(std::unique_ptr<snake_body>&& body, std::string skin);

    snake_body& get_body() const;

    terrain& get_terrain() const;

    int get_length() const;

    void update();

    void turn_left();

    void turn_right();

    void grow(int size);

    void shrink(int size);

public:

    dead_snake_flag is_dead;

    snake_boolean_parameter invulnerability_bonus;

    snake_integer_parameter speed;

    std::string skin;

private:

    void throw_if_dead();

    bool is_time_to_advance_body() const;

private:

    std::unique_ptr<snake_body> body;

    std::unique_ptr<collision_handler> collider;

    int age;

};

int get_snake_update_interval(snake const& s);

}
#pragma once

#include "snake_overflow/collision_handler.hpp"
#include "snake_overflow/dead_snake_flag.hpp"
#include "snake_overflow/snake_boolean_parameter.hpp"
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

    void advance();

    void turn_left();

    void turn_right();

    void grow(int size);

    void shrink(int size);

public:

    dead_snake_flag is_dead;

    snake_boolean_parameter invulnerability_bonus;

    std::string skin;

private:

    void throw_if_dead();

private:

    std::unique_ptr<snake_body> body;

    std::unique_ptr<collision_handler> collider;

};

}
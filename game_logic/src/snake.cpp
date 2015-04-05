#include "stdafx.hpp"

#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

snake::snake(std::unique_ptr<snake_body>&& body, std::string skin)
    : body{std::move(body)}
    , skin(std::move(skin))
    , is_dead{false}
    , invulnerability_bonus{false, is_dead}
    , advancement_interval{4, is_dead, 1, 5}
    , age{0}
{
    this->collider = std::make_unique<collision_handler>(*this, this->is_dead);
}

snake_body& snake::get_body() const
{
    return *(this->body);
}

terrain& snake::get_terrain() const
{
    return this->body->get_terrain();
}

int snake::get_length() const
{
    return this->body->get_length();
}

void snake::update()
{
    if (this->is_dead)
    {
        return;
    }

    if (this->age % this->advancement_interval == 0)
    {
        this->body->advance();
    }

    ++(this->age);
}

void snake::turn_left()
{
    throw_if_dead();

    this->body->turn_left();
}

void snake::turn_right()
{
    throw_if_dead();

    this->body->turn_right();
}

void snake::grow(int const size)
{
    throw_if_dead();

    this->body->grow(size);
}

void snake::shrink(int const size)
{
    throw_if_dead();

    this->body->shrink(size);
}

void snake::throw_if_dead()
{
    if (this->is_dead)
    {
        throw dead_snake_exception{};
    }
}

}
#include "stdafx.hpp"

#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

snake::snake(std::unique_ptr<snake_body>&& body)
    : body{std::move(body)}
    , is_dead{false}
    , invulnerability_bonus{false, is_dead}
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

void snake::advance()
{
    throw_if_dead();

    this->body->advance();
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
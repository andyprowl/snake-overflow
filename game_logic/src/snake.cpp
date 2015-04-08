#include "stdafx.hpp"

#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

snake::snake(std::unique_ptr<snake_body>&& body, std::string skin)
    : body{std::move(body)}
    , skin(std::move(skin))
    , is_dead{false}
    , invulnerability_bonus{false, is_dead}
    , speed{2, is_dead, 1, 5}
    , age{0}
    , next_action{maneuvre::straight_move}
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

    if (is_time_to_move_body())
    {
        move_body();
    }

    ++(this->age);
}

void snake::turn_left()
{
    throw_if_dead();

    next_action = maneuvre::left_turn;
}

void snake::turn_right()
{
    throw_if_dead();

    next_action = maneuvre::right_turn;
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

bool snake::is_time_to_move_body() const
{
    auto const update_interval = get_snake_update_interval(*this);

    return (this->age % update_interval == 0);
}

void snake::move_body()
{
    if (this->next_action == maneuvre::left_turn)
    {
        this->body->turn_left();
    }
    else if (this->next_action == maneuvre::right_turn)
    {
        this->body->turn_right();
    }

    this->body->advance();

    this->next_action = maneuvre::straight_move;
}

int get_snake_update_interval(snake const& s)
{
    return *(s.speed.maximum_value) - s.speed + 1;
}

}
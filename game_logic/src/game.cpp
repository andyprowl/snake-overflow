#include "stdafx.hpp"

#include "snake_overflow/game.hpp"
#include <algorithm>

namespace snake_overflow
{

game::game(std::unique_ptr<terrain>&& habitat, std::unique_ptr<snake>&& hero)
    : habitat{std::move(habitat)}
    , hero{std::move(hero)}
    , score{0}
    , is_over{false}
    , is_paused{false}
{
    this->collider = std::make_unique<collision_handler>(*this);
}

terrain& game::get_terrain() const
{
    return *(this->habitat);
}

snake& game::get_snake() const
{
    return *(this->hero);
}

void game::update()
{
    if (!is_game_paused())
    {
        this->hero->advance();
    }
}

int game::get_score() const
{
    return this->score;
}

void game::add_points(int const points)
{
    throw_if_game_is_over();

    this->score = std::max(0, this->score + points);
}

bool game::is_game_over() const
{
    return this->is_over;
}

void game::set_game_over()
{
    this->is_over = true;
}

bool game::is_game_paused() const
{
    return this->is_paused;
}

void game::toggle_game_pause()
{
    throw_if_game_is_over();

    this->is_paused = !(this->is_paused);
}

void game::throw_if_game_is_over() const
{
    if (is_game_over())
    {
        throw game_over_exception{};
    }
}

}
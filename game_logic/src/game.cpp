#include "stdafx.hpp"

#include "snake_overflow/game.hpp"
#include <algorithm>

namespace snake_overflow
{

game::game(std::unique_ptr<terrain>&& habitat, 
           std::unique_ptr<snake>&& hero,
           std::unique_ptr<terrain_item_filler>&& habitat_filler)
    : habitat{std::move(habitat)}
    , hero{std::move(hero)}
    , habitat_filler{std::move(habitat_filler)}
    , score{0}
    , is_over{false}
    , is_paused{false}
    , snake_advancement_interval{3}
    , terrain_filling_interval{100}
    , age{0}
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
    if (is_game_paused() || is_game_over())
    {
        return;
    }

    if (this->age % this->snake_advancement_interval == 0)
    {
        this->hero->advance();
    }

    if (this->age % this->terrain_filling_interval == 0)
    {
        this->habitat_filler->fill_terrain();
    }

    ++(this->age);
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

int game::get_snake_advancement_interval() const
{
    return this->snake_advancement_interval;
}

void game::set_snake_advancement_interval(int const interval)
{
    this->snake_advancement_interval = interval;
}

int game::get_terrain_item_filling_interval() const
{
    return this->terrain_filling_interval;
}

void game::set_terrain_item_filling_interval(int const interval)
{
    this->terrain_filling_interval = interval;
}

void game::throw_if_game_is_over() const
{
    if (is_game_over())
    {
        throw game_over_exception{};
    }
}

}
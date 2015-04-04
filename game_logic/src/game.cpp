#include "stdafx.hpp"

#include "snake_overflow/game.hpp"

namespace snake_overflow
{

game::game(std::unique_ptr<terrain>&& habitat, 
           std::unique_ptr<snake>&& hero,
           std::unique_ptr<terrain_item_filler>&& habitat_filler)
    : is_game_over{false, hero->is_dead}
    , is_game_paused{false, is_game_over}
    , score{0, is_game_over, 0, boost::none}
    , snake_advancement_interval{4, is_game_over, 1, boost::none}
    , terrain_filling_interval{100, is_game_over, 1, boost::none}
    , habitat{std::move(habitat)}
    , hero{std::move(hero)}
    , habitat_filler{std::move(habitat_filler)}
    , age{0}
{
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
    if (this->is_game_paused || this->is_game_over)
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

void game::throw_if_game_is_over() const
{
    if (this->is_game_over)
    {
        throw game_over_exception{};
    }
}

void toggle_game_pause(game& g)
{
    g.is_game_paused = !(g.is_game_paused);
}

}
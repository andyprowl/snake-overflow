#include "stdafx.hpp"

#include "snake_overflow/game.hpp"
#include <algorithm>

namespace snake_overflow
{

game::game(std::unique_ptr<terrain>&& habitat, std::unique_ptr<snake>&& hero)
    : habitat{std::move(habitat)}
    , hero{std::move(hero)}
    , score{0}
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

int game::get_score() const
{
    return this->score;
}

void game::add_points(int const points)
{
    this->score = std::max(0, this->score + points);
}

}
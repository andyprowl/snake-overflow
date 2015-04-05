#include "stdafx.hpp"

#include "snake_overflow/game_map.hpp"

namespace snake_overflow
{

game_map::game_map(std::string name, std::unique_ptr<terrain>&& ground)
    : name(std::move(name))
    , ground{std::move(ground)}
{
}

std::unique_ptr<game_map> game_map::clone() const
{
    return std::make_unique<game_map>(this->name, this->ground->clone());
}

std::string game_map::get_name() const
{
    return this->name;
}

terrain& game_map::get_terrain() const
{
    return *(this->ground);
}

}
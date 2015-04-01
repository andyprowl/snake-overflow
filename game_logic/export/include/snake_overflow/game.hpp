#pragma once

#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow
{
    
class game
{

public:

    game(std::unique_ptr<terrain>&& habitat, std::unique_ptr<snake>&& hero);

    terrain& get_terrain() const;

    snake& get_snake() const;

    int get_score() const;

    void add_points(int points);

private:

    std::unique_ptr<terrain> habitat;
    
    std::unique_ptr<snake> hero;

    int score;

};

}
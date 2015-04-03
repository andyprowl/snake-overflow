#pragma once

#include "snake_overflow/game_boolean_parameter.hpp"
#include "snake_overflow/game_integer_parameter.hpp"
#include "snake_overflow/game_over_flag.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_item_filler.hpp"

namespace snake_overflow
{

class game
{

public:

    game(std::unique_ptr<terrain>&& habitat, 
         std::unique_ptr<snake>&& hero,
         std::unique_ptr<terrain_item_filler>&& habitat_filler);

    terrain& get_terrain() const;

    snake& get_snake() const;

    void update();

public:

    game_over_flag is_game_over;

    game_boolean_parameter is_game_paused;

    game_integer_parameter score;

    game_integer_parameter snake_advancement_interval;

    game_integer_parameter terrain_filling_interval;

private:

    void throw_if_game_is_over() const;

private:

    std::unique_ptr<terrain> habitat;
    
    std::unique_ptr<snake> hero;

    std::unique_ptr<terrain_item_filler> habitat_filler;

    int age;

};

void toggle_game_pause(game& g);

}
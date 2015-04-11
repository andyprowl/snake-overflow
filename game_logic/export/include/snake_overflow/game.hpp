#pragma once

#include "snake_overflow/game_boolean_parameter.hpp"
#include "snake_overflow/game_integer_parameter.hpp"
#include "snake_overflow/game_map.hpp"
#include "snake_overflow/game_over_flag.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain_item_filler.hpp"

namespace snake_overflow
{

class high_scores_rankings;

class game
{

public:

    game(std::unique_ptr<game_map>&& m, 
         std::unique_ptr<snake>&& hero,
         std::unique_ptr<terrain_item_filler>&& habitat_filler,
         high_scores_rankings& rankings);

    game_map& get_map() const;

    terrain& get_terrain() const;

    snake& get_snake() const;

    void update();

public:

    game_over_flag is_game_over;

    game_boolean_parameter is_game_paused;

    game_integer_parameter score;

    game_integer_parameter terrain_filling_interval;

private:

    void throw_if_game_is_over() const;

    void fill_terrain_if_due_time() const;
    
    void make_all_items_age() const;

    void add_score_to_rankings_if_game_is_over() const;

private:

    std::unique_ptr<game_map> habitat;
    
    std::unique_ptr<snake> hero;

    std::unique_ptr<terrain_item_filler> habitat_filler;

    high_scores_rankings& rankings;

    int age;

};

void toggle_game_pause(game& g);

}
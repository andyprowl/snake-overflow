#pragma once

#include "snake_overflow/collision_handler.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_item_filler.hpp"

namespace snake_overflow
{

class game_over_exception : public virtual std::exception
{
};
    
class game
{

public:

    game(std::unique_ptr<terrain>&& habitat, 
         std::unique_ptr<snake>&& hero,
         std::unique_ptr<terrain_item_filler>&& habitat_filler);

    terrain& get_terrain() const;

    snake& get_snake() const;

    void update();

    int get_score() const;

    void add_points(int points);

    bool is_game_over() const;

    void set_game_over();

    bool is_game_paused() const;

    void toggle_game_pause();

    int get_snake_advancement_interval() const;

    void set_snake_advancement_interval(int interval);

    int get_terrain_item_filling_interval() const;

    void set_terrain_item_filling_interval(int interval);

private:

    void throw_if_game_is_over() const;

private:

    std::unique_ptr<terrain> habitat;
    
    std::unique_ptr<snake> hero;

    std::unique_ptr<terrain_item_filler> habitat_filler;

    std::unique_ptr<collision_handler> collider;

    int score;

    bool is_over;

    bool is_paused;

    int snake_advancement_interval;

    int terrain_filling_interval;

    int age;

};

}
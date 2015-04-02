#pragma once

#include "snake_overflow/collision_handler.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow
{

class game_over_exception : public virtual std::exception
{
};
    
class game
{

public:

    game(std::unique_ptr<terrain>&& habitat, std::unique_ptr<snake>&& hero);

    terrain& get_terrain() const;

    snake& get_snake() const;

    int get_score() const;

    void add_points(int points);

    bool is_game_over() const;

    void set_game_over();

    bool is_game_paused() const;

    void toggle_game_pause();

private:

    void throw_if_game_is_over() const;

private:

    std::unique_ptr<terrain> habitat;
    
    std::unique_ptr<snake> hero;

    std::unique_ptr<collision_handler> collider;

    int score;

    bool is_over;

    bool is_paused;

};

}
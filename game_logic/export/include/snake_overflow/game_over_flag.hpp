#pragma once

namespace snake_overflow
{

class dead_snake_flag;

class game_over_exception : public virtual std::exception
{
};
    
class game_over_flag
{

public:

    game_over_flag(bool is_over, dead_snake_flag& snake_death);

    game_over_flag(game_over_flag const& rhs) = default;

    game_over_flag& operator = (game_over_flag const& rhs) = delete;

    void set();

    operator bool () const;

    ~game_over_flag() = default;

private:

    bool is_over;

    dead_snake_flag& snake_death;

};

}
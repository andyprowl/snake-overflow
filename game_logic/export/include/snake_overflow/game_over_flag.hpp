#pragma once

namespace snake_overflow
{

class game_over_exception : public virtual std::exception
{
};
    
class game_over_flag
{

public:

    game_over_flag(bool is_over);

    game_over_flag(game_over_flag const& rhs) = default;

    game_over_flag& operator = (game_over_flag const& rhs) = delete;

    game_over_flag& operator = (bool over);

    operator bool () const;

    ~game_over_flag() = default;

private:

    bool is_over;

};

}
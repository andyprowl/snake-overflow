#pragma once

namespace snake_overflow
{

enum class game_over_continuation_option
{
    restart_game,
    change_map
};

class continuation_option_setter
{

public:

    virtual ~continuation_option_setter() = default;

    virtual void set_continuation_option(
        game_over_continuation_option option) = 0;

};

}
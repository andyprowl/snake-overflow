#pragma once

namespace snake_overflow
{

class game_over_flag;

class game_boolean_parameter
{

public:

    game_boolean_parameter(bool value, game_over_flag& game_over);

    game_boolean_parameter(game_boolean_parameter const& rhs) = default;

    game_boolean_parameter& operator = (
        game_boolean_parameter const& rhs) = delete;

    game_boolean_parameter& operator = (bool value);

    operator bool () const;

    ~game_boolean_parameter() = default;

private:

    bool value;

    game_over_flag& game_over;

};

}
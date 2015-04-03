#pragma once

#include <boost/optional.hpp>

namespace snake_overflow
{

class game_over_flag;

class game_integer_parameter
{

public:

    game_integer_parameter(int value, 
                           game_over_flag& game_over,
                           boost::optional<int> minimum_value,
                           boost::optional<int> maximum_value);

    game_integer_parameter(game_integer_parameter const& rhs) = default;

    game_integer_parameter& operator = (
        game_integer_parameter const& rhs) = delete;

    game_integer_parameter& operator = (int new_value);

    game_integer_parameter& operator += (int delta);

    game_integer_parameter& operator -= (int delta);

    operator int () const;

    ~game_integer_parameter() = default;

private:

    void throw_if_game_over() const;

    int cap_value(int v) const;

    int cap_to_minimum(int v) const;

    int cap_to_maximum(int v) const;

private:

    int value;

    game_over_flag& game_over;

    boost::optional<int> minimum_value;

    boost::optional<int> maximum_value;

};

}
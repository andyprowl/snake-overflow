#pragma once

#include <boost/optional.hpp>

namespace snake_overflow
{

class dead_snake_flag;

class snake_integer_parameter
{

public:

    snake_integer_parameter(int value, 
                           dead_snake_flag& death_flag,
                           boost::optional<int> minimum_value,
                           boost::optional<int> maximum_value);

    snake_integer_parameter(snake_integer_parameter const& rhs) = default;

    snake_integer_parameter& operator = (
        snake_integer_parameter const& rhs) = delete;

    snake_integer_parameter& operator = (int new_value);

    snake_integer_parameter& operator += (int delta);

    snake_integer_parameter& operator -= (int delta);

    operator int () const;

    ~snake_integer_parameter() = default;

public:

    boost::optional<int> minimum_value;

    boost::optional<int> maximum_value;

private:

    void throw_if_snake_is_dead() const;

    int cap_value(int v) const;

    int cap_to_minimum(int v) const;

    int cap_to_maximum(int v) const;

private:

    int value;

    dead_snake_flag& death_flag;

};

}
#pragma once

namespace snake_overflow
{

class dead_snake_flag;

class snake_boolean_parameter
{

public:

    snake_boolean_parameter(bool value, dead_snake_flag& dead_snake);

    snake_boolean_parameter(snake_boolean_parameter const& rhs) = default;

    snake_boolean_parameter& operator = (
        snake_boolean_parameter const& rhs) = delete;

    snake_boolean_parameter& operator = (bool value);

    operator bool () const;

    ~snake_boolean_parameter() = default;

private:

    bool value;

    dead_snake_flag& dead_snake;

};

}
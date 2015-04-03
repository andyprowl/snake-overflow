#pragma once

namespace snake_overflow
{

class dead_snake_exception : public virtual std::exception
{
};
    
class dead_snake_flag
{

public:

    dead_snake_flag(bool is_dead);

    dead_snake_flag(dead_snake_flag const& rhs) = default;

    dead_snake_flag& operator = (dead_snake_flag const& rhs) = delete;

    void set();

    operator bool () const;

    ~dead_snake_flag() = default;

private:

    bool is_dead;

};

}
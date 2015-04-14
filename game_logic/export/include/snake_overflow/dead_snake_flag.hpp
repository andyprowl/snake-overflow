#pragma once

#include <functional>
#include <boost/signals2/connection.hpp>
#include <boost/signals2/signal.hpp>

namespace snake_overflow
{

class dead_snake_exception : public virtual std::exception
{
};
    
class dead_snake_flag
{

public:

    using death_event_handler = std::function<void()>;

public:

    dead_snake_flag(bool is_dead);

    dead_snake_flag(dead_snake_flag const& rhs) = default;

    dead_snake_flag& operator = (dead_snake_flag const& rhs) = delete;

    void set();

    operator bool () const;

    ~dead_snake_flag() = default;

    boost::signals2::connection register_death_event_handler(
        death_event_handler h);

private:

    bool is_dead;

    boost::signals2::signal<void()> on_death;

};

}
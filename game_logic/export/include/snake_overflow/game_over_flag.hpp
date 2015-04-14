#pragma once

#include <functional>
#include <boost/signals2/connection.hpp>
#include <boost/signals2/signal.hpp>

namespace snake_overflow
{

class dead_snake_flag;

class game_over_exception : public virtual std::exception
{
};
    
class game_over_flag
{

public:

    using game_over_event_handler = std::function<void()>;

public:

    game_over_flag(bool is_over, dead_snake_flag& snake_death);

    game_over_flag(game_over_flag const& rhs) = default;

    game_over_flag& operator = (game_over_flag const& rhs) = delete;

    void set();

    operator bool () const;

    ~game_over_flag() = default;

    boost::signals2::connection register_game_over_event_handler(
        game_over_event_handler h);

private:

    void on_snake_death();

    void set_flag_and_fire_event();

private:

    bool is_over;

    dead_snake_flag& snake_death;

    boost::signals2::signal<void()> on_game_over;

};

}
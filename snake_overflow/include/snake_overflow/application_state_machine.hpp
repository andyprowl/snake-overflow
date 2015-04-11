#pragma once

#include <boost/optional.hpp>

namespace snake_overflow
{

class game_playing_phase;
class interaction_phase;
class map_selection_phase;

class application_state_machine
{

public:

    virtual ~application_state_machine() = default;

    virtual game_playing_phase& get_game_playing_phase() const = 0;

    virtual map_selection_phase& get_map_selection_phase() const = 0;

    virtual interaction_phase& get_current_phase() const = 0;

    virtual void set_current_phase(
        boost::optional<interaction_phase&> phase) = 0;

};

}
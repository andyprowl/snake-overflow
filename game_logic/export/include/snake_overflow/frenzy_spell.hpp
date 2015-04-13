#pragma once

#include "snake_overflow/spell.hpp"

namespace snake_overflow
{
    
class frenzy_spell : public spell
{
    
public:

    frenzy_spell(int duration);

    virtual void affect(snake& s) override;

    int get_duration() const;

private:

    void stop_affecting_snake_and_cause_self_destruction(snake& s) const;

    void increment_speed_if_starting_to_affect(snake& s);

private:

    int duration;

    bool already_applied;

};

}
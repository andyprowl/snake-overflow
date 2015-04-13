#pragma once

#include "snake_overflow/consumable_item.hpp"

namespace snake_overflow
{
    
class speed_booster : public consumable_item
{

public:
    
    speed_booster(position placement, 
                  game& parent_game, 
                  int lifetime,
                  int spell_duration);

private:

    virtual void handle_picking(snake& s) override;

    void give_snake_frenzy_spell(snake& s) const;

private:

    int spell_duration;

};

}
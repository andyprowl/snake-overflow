#include "stdafx.hpp"

#include "snake_overflow/frenzy_spell.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/speed_booster.hpp"

namespace snake_overflow
{
    
speed_booster::speed_booster(position const placement, 
                             game& parent_game,
                             int const lifetime,
                             int const spell_duration)
    : consumable_item{placement, parent_game, lifetime}
    , spell_duration{spell_duration}
{
}

void speed_booster::handle_picking(snake& s)
{
    give_snake_frenzy_spell(s);
}

void speed_booster::give_snake_frenzy_spell(snake& s) const
{
    auto sp = std::make_unique<frenzy_spell>(this->spell_duration);

    s.add_spell(std::move(sp));    
}

}
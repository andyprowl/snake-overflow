#include "stdafx.hpp"

#include "snake_overflow/consumable_item.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow
{

consumable_item::consumable_item(position const placement, game& parent_game)
    : placement{placement}
    , parent_game{parent_game}
{
}

position consumable_item::get_position() const
{
    return this->placement;
}

void consumable_item::pick(snake& s)
{
    handle_picking(s);

    remove_from_terrain_and_cause_self_destruction();
}

void consumable_item::remove_from_terrain_and_cause_self_destruction()
{
    auto& t = this->parent_game.get_terrain();

    t.remove_item(*this);
}


}
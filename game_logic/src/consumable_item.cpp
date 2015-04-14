#include "stdafx.hpp"

#include "snake_overflow/consumable_item.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow
{

consumable_item::consumable_item(position const placement, 
                                 game& parent_game,
                                 int const lifetime)
    : placement{placement}
    , parent_game{parent_game}
    , lifetime{*this, lifetime}
{
}

position consumable_item::get_position() const
{
    return this->placement;
}

std::unique_ptr<item> consumable_item::pick(snake& s)
{
    handle_picking(s);

    return remove_from_terrain();
}

void consumable_item::age()
{
    this->lifetime.shorten();
}

std::unique_ptr<item> consumable_item::remove_from_terrain()
{
    auto& t = this->parent_game.get_terrain();

    return t.remove_item(*this);
}

}
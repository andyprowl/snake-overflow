#include "stdafx.hpp"

#include "snake_overflow/item_lifetime.hpp"
#include "snake_overflow/consumable_item.hpp"

namespace snake_overflow
{

item_lifetime::item_lifetime(consumable_item& i, int const value)
    : parent_item{i}
    , value{value}
{
}

item_lifetime::operator int () const
{
    return this->value;
}

void item_lifetime::shorten()
{
    --(this->value);

    if (this->value == 0)
    {
        this->parent_item.remove_from_terrain_and_cause_self_destruction();
    }
}

}
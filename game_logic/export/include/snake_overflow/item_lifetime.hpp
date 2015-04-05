#pragma once

namespace snake_overflow
{

class consumable_item;

class item_lifetime
{

public:

    item_lifetime(consumable_item& i, int value);
    
    operator int () const;

    void shorten();

private:

    consumable_item& parent_item;

    int value;

};

}
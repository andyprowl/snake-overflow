#pragma once

#include "snake_overflow/item_spawner.hpp"

namespace snake_overflow { namespace testing
{

class item_spawner_spy : public item_spawner
{

public:

    item_spawner_spy(terrain& ground)
        : item_spawner{ground}
    {
    }

    virtual void spawn(int num_of_items_to_spawn) override
    {
        this->num_of_last_spawned_items = num_of_items_to_spawn;
    }

public:

    int num_of_last_spawned_items = 0;

};

} }
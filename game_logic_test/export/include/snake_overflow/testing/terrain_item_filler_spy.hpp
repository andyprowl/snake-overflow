#pragma once

#include "snake_overflow/terrain_item_filler.hpp"

namespace snake_overflow { namespace testing
{

class terrain_item_filler_spy : public terrain_item_filler
{

public:

    terrain_item_filler_spy(item_spawner& spawner)
        : terrain_item_filler{spawner}
    {
    }

    virtual void fill_terrain() override
    {
        invoked = true;
    }

public:

    bool invoked = false;

};

} }
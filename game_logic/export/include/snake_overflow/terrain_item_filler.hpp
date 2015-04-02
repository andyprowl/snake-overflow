#pragma once

namespace snake_overflow
{

class item_spawner;

class terrain_item_filler
{

public:

    terrain_item_filler(item_spawner& spawner);

    virtual void fill_terrain() = 0;

protected:

    item_spawner& spawner;

};

}
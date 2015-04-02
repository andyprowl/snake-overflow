#pragma once

namespace snake_overflow
{

class terrain;

class item_spawner
{

public:

    item_spawner(terrain& ground);

    virtual void spawn(int num_of_items_to_spawn) = 0;
 
public:

    terrain& ground;

};

}
#pragma once

namespace snake_overflow
{

class terrain;

class item_spawner
{

public:

    item_spawner(terrain& world);

private:

    terrain& world;

};

}
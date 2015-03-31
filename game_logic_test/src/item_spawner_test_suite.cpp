#include "stdafx.hpp"

#include "snake_overflow/item_spawner.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Test;

class ItemSpawner : public Test
{

protected:

    virtual void SetUp() override
    {
        auto builder = terrain_builder{this->t};

        builder.add_cube({0, 0, 0}, 3, "", rgba_color::white(), true);
    }

protected:

    terrain t;

    item_spawner spawner{t};

};

} }
#include "stdafx.hpp"

#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/block.hpp"
#include "snake_overflow/point.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class TerrainBuilder : public Test
{

protected:

    terrain t;

    terrain_builder builder{t};

};

TEST_THAT(TerrainBuilder,
     WHAT(AddCube),
     WHEN(GivenAnOriginBlockAndASideLength),
     THEN(AddsASeriesOfBlocksLaidOutAsACubeToTheTerrainPassedAtConstruction))
{
    this->builder.add_cube({-1, 3, 4}, 3, "texture.jpg", {0, 0, 0, 255}, true);

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(26u));
}

} }
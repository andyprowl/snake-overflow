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
     WHEN(GivenASideLengthAndAFlagIndicatingThatTheCubeShouldNotBeFull),
     THEN(AddsASeriesOfBlocksLaidOutAsACubeFrameToTheAssociatedTerrain))
{
    this->builder.add_cube({-1, 3, 4}, 
                           3, 
                           "texture.jpg", 
                           {0, 0, 0, 255}, 
                           true,
                           false);

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(26u));
}

TEST_THAT(TerrainBuilder,
     WHAT(AddCube),
     WHEN(GivenASideLengthAndAFlagIndicatingThatTheCubeShouldBeFull),
     THEN(AddsASeriesOfBlocksLaidOutAsAFullCubeToTheAssociatedTerrain))
{
    this->builder.add_cube({-1, 3, 4}, 
                           3, 
                           "texture.jpg", 
                           {0, 0, 0, 255}, 
                           true,
                           true);

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(27u));
}

TEST_THAT(TerrainBuilder,
     WHAT(RemoveCuboid),
     WHEN(GivenAnOriginBlockAndASetOfThreeSizesThatIdentityACuboid),
     THEN(RemovesTheExistingBlocksThatArePartOfTheIdentifyTheCuboid))
{
    this->builder.add_cube({0, 0, 0}, 
                           5, 
                           "texture.jpg", 
                           {0, 0, 0, 255}, 
                           true, 
                           true);

    this->builder.remove_cuboid({1, 2, 1}, {3, 3, 3});

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(98u));
}

} }
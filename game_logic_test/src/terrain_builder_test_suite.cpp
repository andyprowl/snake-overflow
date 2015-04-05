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
     WHEN(GivenASideLength),
     THEN(AddsASeriesOfBlocksLaidOutAsAFullCubeToTheAssociatedTerrain))
{
    this->builder.add_cube({-1, 3, 4}, 
                           3, 
                           "texture.jpg", 
                           {0, 0, 0, 255}, 
                           true);

    auto const blocks = this->t.get_all_blocks();

    ASSERT_THAT(blocks.size(), Eq(27u));
}

TEST_THAT(TerrainBuilder,
     WHAT(AddCube),
     WHEN(WhenASolidCubeIsBeingCreated),
     THEN(CreatesInnerBlocksAsTransparentSolidAndWithoutATexture))
{
    auto const origin = point{-1, 3, 4};

    this->builder.add_cube(origin, 
                           3, 
                           "texture.jpg", 
                           {0, 0, 0, 255}, 
                           true);

    auto const b = this->t.get_block(origin + point{1, 1, 1});

    EXPECT_TRUE(is_block_transparent(b));
    EXPECT_TRUE(b.texture.empty());
}

TEST_THAT(TerrainBuilder,
     WHAT(RemoveBox),
     WHEN(GivenAnOriginBlockAndASetOfThreeSizesThatIdentifyABox),
     THEN(RemovesTheExistingBlocksThatArePartOfTheIdentifiedBox))
{
    this->builder.add_cube({0, 0, 0}, 
                           5, 
                           "texture.jpg", 
                           {0, 0, 0, 255}, 
                           true);

    this->builder.remove_box({1, 2, 1}, {3, 3, 3});

    auto const blocks = this->t.get_all_blocks();

    ASSERT_THAT(blocks.size(), Eq(98u));
}

} }
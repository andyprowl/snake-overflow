#include "stdafx.hpp"

#include "snake_overflow/item_spawner.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"

namespace snake_overflow { namespace testing
{
    
using ::testing::Contains;
using ::testing::Eq;
using ::testing::Test;

class ItemSpawner : public Test
{

protected:

    terrain t;

    terrain_builder builder{this->t};

    item_spawner spawner{t};

};

TEST_THAT(ItemSpawner,
     WHAT(GetValidPositions),
     WHEN(Always),
     THEN(ReturnsOnlyPositionsOnTheNonNeighboringSurfaceOfABlock))
{
    this->builder.add_cube({0, 0, 0}, 2, "", rgba_color::white(), true);

    auto const positions = this->spawner.get_valid_positions();

    ASSERT_THAT(positions.size(), Eq(24));

    EXPECT_THAT(positions, Contains(position{{0, 0, 0}, block_face::front}));    
    EXPECT_THAT(positions, Contains(position{{0, 0, 1}, block_face::front}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 0}, block_face::front}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 1}, block_face::front}));    

    EXPECT_THAT(positions, Contains(position{{0, 1, 0}, block_face::back}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 1}, block_face::back}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 0}, block_face::back}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 1}, block_face::back}));    

    EXPECT_THAT(positions, Contains(position{{0, 0, 0}, block_face::left}));    
    EXPECT_THAT(positions, Contains(position{{0, 0, 1}, block_face::left}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 0}, block_face::left}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 1}, block_face::left}));    

    EXPECT_THAT(positions, Contains(position{{1, 0, 0}, block_face::right}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 1}, block_face::right}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 0}, block_face::right}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 1}, block_face::right}));    

    EXPECT_THAT(positions, Contains(position{{0, 0, 1}, block_face::top}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 1}, block_face::top}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 1}, block_face::top}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 1}, block_face::top}));    

    EXPECT_THAT(positions, Contains(position{{0, 0, 0}, block_face::bottom}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 0}, block_face::bottom}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 0}, block_face::bottom}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 0}, block_face::bottom}));    
}

} }
#include "stdafx.hpp"

#include "snake_overflow/random_item_position_picker.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include <memory>

namespace snake_overflow { namespace testing
{
    
using ::testing::Contains;
using ::testing::Eq;
using ::testing::Test;

class RandomItemPositionPicker : public Test
{

protected:

    virtual void SetUp() override
    {
        this->builder.add_cube({0, 0, 0}, 2, "", rgba_color::white(), true);

        this->picker = std::make_unique<random_item_position_picker>(t);
    }

protected:

    terrain t;

    terrain_builder builder{this->t};

    std::unique_ptr<random_item_position_picker> picker;

};

TEST_THAT(RandomItemPositionPicker,
     WHAT(GetValidPositions),
     WHEN(Always),
     THEN(ReturnsOnlyPositionsOnTheNonNeighboringSurfaceOfABlock))
{
    auto const positions = this->picker->get_valid_positions();

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

// This is more of an integration test, as it involves random behavior.
TEST_THAT(RandomItemPositionPicker,
     WHAT(PickItemPosition),
     WHEN(Always),
     THEN(ReturnsAValidPositionForPlacingAnItem))
{
    auto const pos = this->picker->pick_item_position();

    auto const positions = this->picker->get_valid_positions();

    EXPECT_THAT(positions, Contains(pos));
}

} }
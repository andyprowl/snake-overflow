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
        this->builder.add_cube({0, 0, 0}, 25, "", rgba_color::white(), true);

        this->picker = std::make_unique<random_item_position_picker>(this->t);
    }

protected:

    terrain t;

    terrain_builder builder{t};

    std::unique_ptr<random_item_position_picker> picker;

};

// This is more of an integration test, since it relies on non-deterministic
// behavior.
TEST_THAT(RandomItemPositionPicker,
     WHAT(PickItemPosition),
     WHEN(Always),
     THEN(ReturnsAValidPositionForPlacingAnItem))
{
    auto const pos = this->picker->pick_item_position();

    EXPECT_TRUE(can_place_item_at_position(pos, this->t));
}

} }
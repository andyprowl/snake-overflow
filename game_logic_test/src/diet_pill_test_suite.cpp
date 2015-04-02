#include "stdafx.hpp"

#include "snake_overflow/diet_pill.hpp"
#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "util/repeat.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;

class DietPill : public CubeTerrainGameFixture
{

protected:

    virtual void SetUp() override
    {
        CubeTerrainGameFixture::SetUp();

        auto& g = get_game();

        auto i = std::make_unique<diet_pill>(this->placement, 
                                             g,
                                             this->slim_power);

        this->pill = i.get();

        auto& ground = get_terrain();

        ground.add_item(std::move(i));
    }

protected:

    int slim_power = 1;

    position placement = {{1, 0, 2}, block_face::front};

    diet_pill* pill;

};

TEST_THAT(DietPill,
     WHAT(GetPosition),
     WHEN(Always),
     THEN(ReturnsThePositionPassedAtConstruction))
{
    EXPECT_THAT(this->pill->get_position(), Eq(this->placement));
}

TEST_THAT(DietPill,
     WHAT(SlimPower),
     WHEN(ImmediatelyAfterConstruction),
     THEN(HasTheValuePassedAtConstruction))
{
    EXPECT_THAT(this->pill->slim_power, Eq(this->slim_power));
}

TEST_THAT(DietPill,
     WHAT(Pick),
     WHEN(GivenAPickingSnake),
     THEN(MakesTheSnakeShrinkByItsSlimPower))
{
    auto& s = get_snake();

    this->pill->pick(s);

    util::repeat(10, [&s] { s.advance(); });

    auto const expected_length = this->initial_snake_length - 
                                 this->slim_power;

    EXPECT_THAT(s.get_length(), Eq(expected_length));
}

TEST_THAT(DietPill,
     WHAT(Pick),
     WHEN(Always),
     THEN(RemovesTheItemFromTheTerrain))
{
    auto& s = get_snake();

    this->pill->pick(s);

    auto& t = get_terrain();

    auto const b = t.get_block(placement.location);
    
    EXPECT_THAT(b.items.size(), Eq(0u));
}

} }
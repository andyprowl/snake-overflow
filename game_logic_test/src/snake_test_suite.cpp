#include "stdafx.hpp"

#include "snake_overflow/game_logic/cube_builder.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/snake.hpp"
#include "snake_overflow/game_logic/territory.hpp"

namespace snake_overflow { namespace game_logic { namespace testing
{

using ::testing::Ge;
using ::testing::Test;

class Snake : public Test
{

protected:

    virtual void SetUp() override
    {
        cube_builder builder{habitat};

        builder.add_cube({0, 0, 0}, 4);
    }

protected:

    territory habitat;

    position start_position{{0, 0, 0}, surface::front};

    int initial_length = 3;

    math::point3d initial_direction = math::point3d::z_unit();

    snake s{habitat, start_position, initial_length, initial_direction};

};

TEST_THAT(Snake,
     WHAT(GetBody),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsASequenceOfPositionsOfTheLengthPassedAtConstruction))
{
    auto const body = this->s.get_body();

    EXPECT_THAT(body.size(), Ge(this->initial_length));
}

} } }
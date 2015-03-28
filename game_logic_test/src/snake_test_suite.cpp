#include "stdafx.hpp"

#include "snake_overflow/game_logic/cube_builder.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/snake.hpp"
#include "snake_overflow/game_logic/territory.hpp"
#include "util/repeat.hpp"
#include "util/sequence.hpp"
#include <memory>

namespace snake_overflow { namespace game_logic { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class Snake : public Test
{

protected:

    virtual void SetUp() override
    {
        cube_builder builder{this->habitat};

        builder.add_cube({0, 0, 0}, 5);

        this->s = std::make_unique<snake>(habitat, 
                                          initial_dynamics, 
                                          initial_length);
    }

protected:

    territory habitat;

    position start_position{{0, 0, 0}, surface::front};

    int initial_length = 3;

    dynamics initial_dynamics = {start_position, 
                                 direction{cartesian_axis::z, 
                                           orientation::positive}};

    std::unique_ptr<snake> s;

};

TEST_THAT(Snake,
     WHAT(GetBody),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsASequenceOfPositionsOfTheLengthPassedAtConstruction))
{
    auto const body = this->s->get_body();

    EXPECT_THAT(body.size(), Eq(this->initial_length));
}

TEST_THAT(Snake,
     WHAT(GetBody),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsASetOfConsecutivePositionsStartingFromTheInitialOne))
{
    auto const body = this->s->get_body();

    ASSERT_THAT(body.size(), Eq(this->initial_length));    

    EXPECT_THAT(body[0], Eq(this->start_position));

    auto const dir = get_direction_vector(this->initial_dynamics.dir);    
    for (auto const i : util::sequence(0, this->initial_length))
    {
        auto expected_block = this->start_position.block_origin + i * dir;
        EXPECT_THAT(body[i].block_origin, Eq(expected_block));
    }
}

TEST_THAT(Snake,
     WHAT(GetDirection),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsTheDirectionPassedAtConstruction))
{
    auto const dir = this->s->get_direction();

    EXPECT_THAT(dir, Eq(initial_dynamics.dir));
}

TEST_THAT(Snake,
     WHAT(Advance),
     WHEN(Always),
     THEN(ShiftsTheBodyOfTheSnakeOnePositionTowardsTheCurrentDirection))
{
    util::repeat(4, [this] { this->s->advance(); });

    auto const body = this->s->get_body();

    ASSERT_THAT(body.size(), Eq(3u));

    EXPECT_THAT(body[0], Eq(position{{0, 0, 4}, surface::front}));
    EXPECT_THAT(body[1], Eq(position{{0, 0, 4}, surface::top}));
    EXPECT_THAT(body[2], Eq(position{{0, 1, 4}, surface::top}));
}

TEST_THAT(Snake,
     WHAT(Grow),
     WHEN(GivenASize),
     THEN(MakesFollowingAdvancementsGrowTheSnakeRatherThanShiftingIt))
{
    this->s->grow(2);

    util::repeat(4, [this] { this->s->advance(); });

    auto const body = this->s->get_body();

    ASSERT_THAT(body.size(), Eq(5u));

    EXPECT_THAT(body[0], Eq(position{{0, 0, 2}, surface::front}));
    EXPECT_THAT(body[1], Eq(position{{0, 0, 3}, surface::front}));
    EXPECT_THAT(body[2], Eq(position{{0, 0, 4}, surface::front}));
    EXPECT_THAT(body[3], Eq(position{{0, 0, 4}, surface::top}));
    EXPECT_THAT(body[4], Eq(position{{0, 1, 4}, surface::top}));
}

} } }
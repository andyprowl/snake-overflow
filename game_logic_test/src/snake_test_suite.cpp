#include "stdafx.hpp"

#include "snake_overflow/cube_builder.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/territory.hpp"
#include "util/repeat.hpp"
#include "util/sequence.hpp"
#include <memory>

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class Snake : public Test
{

protected:

    virtual void SetUp() override
    {
        auto builder = cube_builder{this->habitat};

        builder.add_cube({0, 0, 0}, this->territory_side_length);

        this->s = std::make_unique<snake>(habitat, 
                                          initial_dynamics, 
                                          initial_length);
    }

protected:

    int territory_side_length = 5;

    territory habitat;

    point initial_location = {0, 0, 0};

    block_face initial_face = block_face::front;

    position initial_position{initial_location, initial_face};

    canonical_direction initial_direction{canonical_axis::z, 
                                          orientation::positive};

    int initial_length = 3;

    dynamics initial_dynamics = {initial_location, 
                                {initial_face, initial_direction}};

    std::unique_ptr<snake> s;

};

TEST_THAT(Snake,
     WHAT(GetTrail),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsASequenceOfDynamicsOfTheLengthPassedAtConstruction))
{
    auto const trail = this->s->get_trail();

    EXPECT_THAT(trail.size(), Eq(this->initial_length));
}

TEST_THAT(Snake,
     WHAT(GetTrail),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsASetOfConsecutiveDynamicsStartingFromTheInitialOne))
{
    auto const trail = this->s->get_trail();

    ASSERT_THAT(trail.size(), Eq(this->initial_length));    

    EXPECT_THAT(trail[0], Eq(this->initial_dynamics));

    auto const dir = get_dynamics_direction_vector(this->initial_dynamics);    
    for (auto const i : util::sequence(0, this->initial_length))
    {
        auto expected_block = this->initial_location + i * dir;
        EXPECT_THAT(trail[i].location, Eq(expected_block));
    }
}

TEST_THAT(Snake,
     WHAT(GetDirection),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsTheDirectionPassedAtConstruction))
{
    auto const dir = this->s->get_direction();

    EXPECT_THAT(dir, Eq(this->initial_direction));
}

TEST_THAT(Snake,
     WHAT(Advance),
     WHEN(Always),
     THEN(ShiftsTheBodyOfTheSnakeOnePositionTowardsTheCurrentDirection))
{
    util::repeat(4, [this] { this->s->advance(); });

    auto const trail = this->s->get_trail();

    ASSERT_THAT(trail.size(), Eq(3u));

    EXPECT_THAT(get_dynamics_position(trail[0]), 
                Eq(position{{0, 0, 4}, block_face::front}));

    EXPECT_THAT(get_dynamics_position(trail[1]), 
                Eq(position{{0, 0, 4}, block_face::top}));

    EXPECT_THAT(get_dynamics_position(trail[2]), 
                Eq(position{{0, 1, 4}, block_face::top}));
}

TEST_THAT(Snake,
     WHAT(Grow),
     WHEN(GivenASize),
     THEN(MakesFollowingAdvancementsGrowTheSnakeRatherThanShiftingIt))
{
    this->s->grow(2);

    util::repeat(4, [this] { this->s->advance(); });

    auto const trail = this->s->get_trail();

    ASSERT_THAT(trail.size(), Eq(5u));

    EXPECT_THAT(get_dynamics_position(trail[0]), 
                Eq(position{{0, 0, 2}, block_face::front}));
    
    EXPECT_THAT(get_dynamics_position(trail[1]), 
                Eq(position{{0, 0, 3}, block_face::front}));
    
    EXPECT_THAT(get_dynamics_position(trail[2]), 
                Eq(position{{0, 0, 4}, block_face::front}));
    
    EXPECT_THAT(get_dynamics_position(trail[3]), 
                Eq(position{{0, 0, 4}, block_face::top}));
    
    EXPECT_THAT(get_dynamics_position(trail[4]), 
                Eq(position{{0, 1, 4}, block_face::top}));
}

TEST_THAT(Snake,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheFrontSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItLeft))
{
    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_z()));
}

TEST_THAT(Snake,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheFrontSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItRight))
{
    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_z()));
}

TEST_THAT(Snake,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheBackSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItLeft))
{
    util::repeat(8, [this] { this->s->advance(); });

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_z()));
}

TEST_THAT(Snake,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheBackSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItRight))
{
    util::repeat(8, [this] { this->s->advance(); });

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_z()));
}

TEST_THAT(Snake,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheLeftSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItLeft))
{
    this->s->turn_left();
    util::repeat(3, [this] { this->s->advance(); });

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(Snake,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheLeftSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItLeft))
{
    this->s->turn_left();
    util::repeat(3, [this] { this->s->advance(); });

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(Snake,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheRightSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItRight))
{
    this->s->turn_right();
    util::repeat(7, [this] { this->s->advance(); });

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(Snake,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheRightSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItRight))
{
    this->s->turn_right();
    util::repeat(7, [this] { this->s->advance(); });

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(Snake,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheTopSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItRight))
{
    util::repeat(4, [this] { this->s->advance(); });

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(Snake,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheTopSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItRight))
{
    util::repeat(4, [this] { this->s->advance(); });

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(Snake,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheBottomSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItRight))
{
    this->s->turn_right();
    this->s->advance();
    this->s->turn_right();
    util::repeat(3, [this] { this->s->advance(); });

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->s->turn_left();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(Snake,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheBottomSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeByTurningItRight))
{
    this->s->turn_right();
    this->s->advance();
    this->s->turn_right();
    util::repeat(3, [this] { this->s->advance(); });

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->s->turn_right();
    EXPECT_THAT(this->s->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(Snake,
     WHAT(GetTrail),
     WHEN(Always),
     THEN(ReturnsInformationOnTheManeuvreMadeAtEachPositionInTheTrail))
{
    this->s->grow(3);

    this->s->advance();
    this->s->turn_right();
    this->s->advance();
    this->s->advance();
    this->s->turn_right();
    this->s->advance();

    auto const trail = this->s->get_trail();
    ASSERT_THAT(trail.size(), Eq(6u));

    EXPECT_THAT(trail[0].action, Eq(maneuvre::move_forward));
    EXPECT_THAT(trail[1].action, Eq(maneuvre::move_forward));
    EXPECT_THAT(trail[2].action, Eq(maneuvre::turn_right));
    EXPECT_THAT(trail[3].action, Eq(maneuvre::move_forward));
    EXPECT_THAT(trail[4].action, Eq(maneuvre::turn_right));
    EXPECT_THAT(trail[5].action, Eq(maneuvre::move_forward));
}

TEST_THAT(Snake,
     WHAT(GetLength),
     WHEN(Always),
     THEN(ReturnsTheNumberOfPartsInTheBodyOfTheSnake))
{
    EXPECT_THAT(this->s->get_length(), Eq(this->initial_length));

    this->s->grow(3);

    this->s->advance();
    EXPECT_THAT(this->s->get_length(), Eq(this->initial_length + 1));

    this->s->turn_right();

    this->s->advance();
    EXPECT_THAT(this->s->get_length(), Eq(this->initial_length + 2));

    this->s->advance();
    EXPECT_THAT(this->s->get_length(), Eq(this->initial_length + 3));

    this->s->turn_right();

    this->s->advance();
    EXPECT_THAT(this->s->get_length(), Eq(this->initial_length + 3));
}

} }
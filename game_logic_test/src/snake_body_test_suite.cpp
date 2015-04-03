#include "stdafx.hpp"

#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/snake_body.hpp"
#include "snake_overflow/terrain.hpp"
#include "util/repeat.hpp"
#include "util/sequence.hpp"
#include <memory>

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class SnakeBody : public Test
{

protected:

    virtual void SetUp() override
    {
        auto builder = terrain_builder{this->habitat};

        builder.add_cube({0, 0, 0}, 
                         this->terrain_side_length, 
                         "texture.jpg", 
                         {255, 255, 255, 255},
                         true);

        this->body = std::make_unique<snake_body>(habitat, 
                                                  initial_footprint, 
                                                  initial_length);
    }

protected:

    int terrain_side_length = 5;

    terrain habitat;

    point initial_location = {0, 0, 0};

    block_face initial_face = block_face::front;

    position initial_position{initial_location, initial_face};

    canonical_direction initial_direction{canonical_axis::z, 
                                          orientation::positive};

    int initial_length = 3;

    footprint initial_footprint = {initial_location, 
                                   {initial_face, initial_direction}};

    std::unique_ptr<snake_body> body;

};

TEST_THAT(SnakeBody,
     WHAT(GetTrail),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsASequenceOfFootprintOfTheLengthPassedAtConstruction))
{
    auto const trail = this->body->get_trail();

    EXPECT_THAT(trail.size(), Eq(this->initial_length));
}

TEST_THAT(SnakeBody,
     WHAT(GetTrail),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsASetOfConsecutiveFootprintStartingFromTheInitialOne))
{
    auto const trail = this->body->get_trail();

    ASSERT_THAT(trail.size(), Eq(this->initial_length));    

    EXPECT_THAT(trail[0].step, Eq(this->initial_footprint));

    auto const dir = get_footprint_direction_vector(this->initial_footprint);    
    for (auto const i : util::sequence(0, this->initial_length))
    {
        auto expected_block = this->initial_location + i * dir;
        EXPECT_THAT(trail[i].step.location, Eq(expected_block));
    }
}

TEST_THAT(SnakeBody,
     WHAT(GetDirection),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsTheDirectionPassedAtConstruction))
{
    auto const dir = this->body->get_direction();

    EXPECT_THAT(dir, Eq(this->initial_direction));
}

TEST_THAT(SnakeBody,
     WHAT(GetTrailHead),
     WHEN(Always),
     THEN(ReturnsTheDynamicsOfTheHeadOfTheSnakeBody))
{
    auto const d1 = this->body->get_trail_head();

    EXPECT_THAT(get_footprint_position(d1.step).location, 
                Eq(point{0, 0, this->initial_length - 1}));

    EXPECT_THAT(get_footprint_direction(d1.step), 
                Eq(canonical_direction::positive_z()));

    this->body->turn_right();
    auto const d2 = this->body->get_trail_head();
    EXPECT_THAT(get_footprint_direction(d2.step), 
                Eq(canonical_direction::positive_x()));
    
}

TEST_THAT(SnakeBody,
     WHAT(Advance),
     WHEN(Always),
     THEN(ShiftsTheBodyOfTheSnakeBodyOnePositionTowardsTheCurrentDirection))
{
    util::repeat(4, [this] { this->body->advance(); });

    auto const trail = this->body->get_trail();

    ASSERT_THAT(trail.size(), Eq(3u));

    EXPECT_THAT(get_footprint_position(trail[0].step), 
                Eq(position{{0, 0, 4}, block_face::front}));

    EXPECT_THAT(get_footprint_position(trail[1].step), 
                Eq(position{{0, 0, 4}, block_face::top}));

    EXPECT_THAT(get_footprint_position(trail[2].step), 
                Eq(position{{0, 1, 4}, block_face::top}));
}

TEST_THAT(SnakeBody,
     WHAT(Advance),
     WHEN(Always),
     THEN(InvokesAllHandlersRegisteredForMovementEvents))
{
    boost::optional<footprint> step;

    this->body->register_movement_handler(
        [&step] (util::value_ref<footprint> fp)
    {
        step = fp;
    });

    this->body->advance();

    auto const expected_step = footprint{
        {0, 0, 3}, 
        {block_face::front, canonical_direction::positive_z()}};

    EXPECT_THAT(*step, Eq(expected_step));
}

TEST_THAT(SnakeBody,
     WHAT(Grow),
     WHEN(GivenASize),
     THEN(MakesFollowingAdvancementsGrowTheSnakeBodyRatherThanShiftingIt))
{
    this->body->grow(2);

    util::repeat(4, [this] { this->body->advance(); });

    auto const trail = this->body->get_trail();

    ASSERT_THAT(trail.size(), Eq(5u));

    EXPECT_THAT(get_footprint_position(trail[0].step), 
                Eq(position{{0, 0, 2}, block_face::front}));
    
    EXPECT_THAT(get_footprint_position(trail[1].step), 
                Eq(position{{0, 0, 3}, block_face::front}));
    
    EXPECT_THAT(get_footprint_position(trail[2].step), 
                Eq(position{{0, 0, 4}, block_face::front}));
    
    EXPECT_THAT(get_footprint_position(trail[3].step), 
                Eq(position{{0, 0, 4}, block_face::top}));
    
    EXPECT_THAT(get_footprint_position(trail[4].step), 
                Eq(position{{0, 1, 4}, block_face::top}));
}

TEST_THAT(SnakeBody,
     WHAT(Shrink),
     WHEN(GivenASize),
     THEN(MakesFollowingAdvancementsShrinkTheSnakeBodyRatherThanShiftingIt))
{
    this->body->grow(1);

    this->body->advance();

    this->body->shrink(2);

    util::repeat(4, [this] { this->body->advance(); });

    auto const trail = this->body->get_trail();

    ASSERT_THAT(trail.size(), Eq(2u));

    EXPECT_THAT(get_footprint_position(trail[0].step), 
                Eq(position{{0, 1, 4}, block_face::top}));

    EXPECT_THAT(get_footprint_position(trail[1].step), 
                Eq(position{{0, 2, 4}, block_face::top}));
}

TEST_THAT(SnakeBody,
     WHAT(Shrink),
     WHEN(GivenASizeWhichWouldReduceTheSnakeBodyToLessThanTwoCells),
     THEN(OnlyShrinksTheSnakeBodyAsShortAsTwoCells))
{
    this->body->shrink(2);

    util::repeat(4, [this] { this->body->advance(); });

    auto const trail = this->body->get_trail();

    ASSERT_THAT(trail.size(), Eq(2u));

    EXPECT_THAT(get_footprint_position(trail[0].step), 
                Eq(position{{0, 0, 4}, block_face::top}));

    EXPECT_THAT(get_footprint_position(trail[1].step), 
                Eq(position{{0, 1, 4}, block_face::top}));
}

TEST_THAT(SnakeBody,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheFrontSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItLeft))
{
    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_z()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheFrontSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItRight))
{
    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_z()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheBackSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItLeft))
{
    util::repeat(8, [this] { this->body->advance(); });

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_z()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheBackSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItRight))
{
    util::repeat(8, [this] { this->body->advance(); });

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_z()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheLeftSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItLeft))
{
    this->body->turn_left();
    util::repeat(3, [this] { this->body->advance(); });

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheLeftSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItLeft))
{
    this->body->turn_left();
    util::repeat(3, [this] { this->body->advance(); });

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheRightSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItRight))
{
    this->body->turn_right();
    util::repeat(7, [this] { this->body->advance(); });

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheRightSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItRight))
{
    this->body->turn_right();
    util::repeat(7, [this] { this->body->advance(); });

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_z()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_z()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheTopSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItRight))
{
    util::repeat(4, [this] { this->body->advance(); });

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheTopSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItRight))
{
    util::repeat(4, [this] { this->body->advance(); });

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnLeft),
     WHEN(WhenWalkingOnTheBottomSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItRight))
{
    this->body->turn_right();
    this->body->advance();
    this->body->turn_right();
    util::repeat(3, [this] { this->body->advance(); });

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->body->turn_left();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(SnakeBody,
     WHAT(TurnRight),
     WHEN(WhenWalkingOnTheBottomSurface),
     THEN(CorrectlyChangesTheDirectionOfMovementOfTheSnakeBodyByTurningItRight))
{
    this->body->turn_right();
    this->body->advance();
    this->body->turn_right();
    util::repeat(3, [this] { this->body->advance(); });

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_x()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::negative_y()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_x()));

    this->body->turn_right();
    EXPECT_THAT(this->body->get_direction(), 
                Eq(canonical_direction::positive_y()));
}

TEST_THAT(SnakeBody,
     WHAT(GetTrail),
     WHEN(Always),
     THEN(ReturnsInformationOnTheManeuvreMadeAtEachPositionInTheTrail))
{
    this->body->grow(3);

    this->body->advance();
    this->body->turn_right();
    this->body->advance();
    this->body->advance();
    this->body->turn_right();
    this->body->advance();

    auto const trail = this->body->get_trail();
    ASSERT_THAT(trail.size(), Eq(6u));

    EXPECT_THAT(trail[0].action, Eq(maneuvre::straight_move));
    EXPECT_THAT(trail[1].action, Eq(maneuvre::straight_move));
    EXPECT_THAT(trail[2].action, Eq(maneuvre::right_turn));
    EXPECT_THAT(trail[3].action, Eq(maneuvre::straight_move));
    EXPECT_THAT(trail[4].action, Eq(maneuvre::right_turn));
    EXPECT_THAT(trail[5].action, Eq(maneuvre::straight_move));
}

TEST_THAT(SnakeBody,
     WHAT(GetLength),
     WHEN(Always),
     THEN(ReturnsTheNumberOfPartsInTheBodyOfTheSnakeBody))
{
    EXPECT_THAT(this->body->get_length(), Eq(this->initial_length));

    this->body->grow(3);

    this->body->advance();
    EXPECT_THAT(this->body->get_length(), Eq(this->initial_length + 1));

    this->body->turn_right();

    this->body->advance();
    EXPECT_THAT(this->body->get_length(), Eq(this->initial_length + 2));

    this->body->advance();
    EXPECT_THAT(this->body->get_length(), Eq(this->initial_length + 3));

    this->body->turn_right();

    this->body->advance();
    EXPECT_THAT(this->body->get_length(), Eq(this->initial_length + 3));
}

TEST_THAT(SnakeBody,
     WHAT(OccupiesPosition),
     WHEN(GivenAPositionThatTheSnakeBodyOccupies),
     THEN(ReturnsTrue))
{
    EXPECT_TRUE(this->body->is_position_in_tail(
                    {{0, 0, 0}, block_face::front}));

    EXPECT_TRUE(this->body->is_position_in_tail(
                    {{0, 0, 1}, block_face::front}));
}

TEST_THAT(SnakeBody,
     WHAT(OccupiesPosition),
     WHEN(GivenAPositionThatTheSnakeBodyDoesNotOccupy),
     THEN(ReturnsFalse))
{
    EXPECT_FALSE(this->body->is_position_in_tail(
                    {{0, 0, 3}, block_face::front}));

    EXPECT_FALSE(this->body->is_position_in_tail(
                    {{1, 0, 1}, block_face::front}));

    EXPECT_FALSE(this->body->is_position_in_tail(
                    {{0, 0, 0}, block_face::bottom}));
}

} }
#include "stdafx.hpp"

#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "snake_overflow/testing/fake_item.hpp"
#include "util/repeat.hpp"

namespace snake_overflow { namespace testing
{
    
using ::testing::Eq;
using ::testing::Gt;
using ::testing::Ne;

class Snake : public CubeTerrainGameFixture
{

protected:

    std::unique_ptr<item> make_item(util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    }

    // The collision handler is implicitly created as part of the game object.

};

TEST_THAT(Snake,
     WHAT(Skin),
     WHEN(ImmediatelyAfterConstruction),
     THEN(HoldsTheNameOfTheSkinPassedAtConstruction))
{
    auto& s = get_snake();

    EXPECT_THAT(s.skin, Eq(this->snake_skin));
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenTheHeadOfTheSnakeCollidesWithAnItem),
     THEN(LetsTheItemBePickedByTheSnake))
{
    auto i = make_item({{0, 0, 4}, block_face::front});

    auto& t = get_terrain();

    t.add_item(std::move(i));

    auto& s = get_snake();

    s.get_body().advance();

    EXPECT_THROW(s.get_body().advance(), item_picked_exception);
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenTheHeadOfTheSnakeCollidesWithAPartOfItsBody),
     THEN(KillsTheSnake))
{
    auto& s = get_snake();

    auto const update_interval = get_snake_update_interval(s);

    s.grow(5);

    s.turn_right();

    util::repeat(update_interval, [&s] { s.update(); });

    s.turn_right();

    util::repeat(update_interval, [&s] { s.update(); });

    s.turn_right();

    s.update();

    EXPECT_TRUE(s.is_dead);
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenTheSnakeIsDead),
     THEN(DoesNothing))
{
    auto& s = get_snake();

    auto& b = s.get_body();

    auto old_head = b.get_trail_head().step;

    s.is_dead.set();

    EXPECT_NO_THROW([&s]
    {
        auto const update_interval = get_snake_update_interval(s);

        util::repeat(update_interval, [&s] { s.update(); });
    });

    EXPECT_THAT(b.get_trail_head().step, Eq(old_head));
}

TEST_THAT(Snake,
     WHAT(TurnLeft),
     WHEN(WhenTheSnakeIsDead),
     THEN(Throws))
{
    auto& s = get_snake();

    s.is_dead.set();

    EXPECT_THROW(s.turn_left(), dead_snake_exception);
}

TEST_THAT(Snake,
     WHAT(TurnRight),
     WHEN(WhenTheSnakeIsDead),
     THEN(Throws))
{
    auto& s = get_snake();

    s.is_dead.set();

    EXPECT_THROW(s.turn_right(), dead_snake_exception);
}

TEST_THAT(Snake,
     WHAT(Grow),
     WHEN(WhenTheSnakeIsDead),
     THEN(Throws))
{
    auto& s = get_snake();

    s.is_dead.set();

    EXPECT_THROW(s.grow(1), dead_snake_exception);
}

TEST_THAT(Snake,
     WHAT(Shrink),
     WHEN(WhenTheSnakeIsDead),
     THEN(Throws))
{
    auto& s = get_snake();

    s.is_dead.set();

    EXPECT_THROW(s.shrink(1), dead_snake_exception);
}

TEST_THAT(Snake,
     WHAT(InvulnerabilityBonus),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToFalse))
{
    auto& s = get_snake();

    EXPECT_FALSE(s.invulnerability_bonus);
}

TEST_THAT(Snake,
     WHAT(InvulnerabilityBonus),
     WHEN(AfterSettingItsValue),
     THEN(EvaluatesToTheNewlySetValue))
{
    auto& s = get_snake();

    s.invulnerability_bonus = true;

    EXPECT_TRUE(s.invulnerability_bonus);
}

TEST_THAT(Snake,
     WHAT(InvulnerabilityBonus),
     WHEN(WhenSettingItsValueAfterTheSnakeHasDied),
     THEN(Throws))
{
    auto& s = get_snake();

    s.is_dead.set();

    EXPECT_THROW((s.invulnerability_bonus = true), dead_snake_exception);
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenCalledForTheNthTimeWithNEqualToTheUpdateInterval),
     THEN(UpdatesTheBody))
{
    auto& s = get_snake();

    auto& body = get_snake_body();

    auto const initial_footprint = body.get_trail_head().step;

    auto const interval = get_snake_update_interval(s);

    s.update();

    auto const next_footprint = body.get_trail_head().step;

    EXPECT_THAT(next_footprint, Ne(initial_footprint));

    util::repeat(interval - 1, [&s] { s.update(); });

    EXPECT_THAT(body.get_trail_head().step, Eq(next_footprint));

    s.update();

    EXPECT_THAT(body.get_trail_head().step, Ne(next_footprint));
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenTheSnakeBitesItselfButHasAPositiveInvulnerabilityBonus),
     THEN(DoesNotKillTheSnake))
{
    auto& s = get_snake();

    s.grow(5);

    s.turn_right();

    s.update();

    s.turn_right();

    s.update();

    s.turn_right();

    s.invulnerability_bonus = true;

    s.update();

    EXPECT_FALSE(s.is_dead);
}

TEST_THAT(Snake,
     WHAT(Speed),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToANonNegativeValue))
{
    auto& s = get_snake();

    EXPECT_THAT(s.speed, Gt(0));
}

TEST_THAT(Snake,
     WHAT(Speed),
     WHEN(AfterSettingAValueGreaterThanOneButLessThanTheMaximum),
     THEN(ReturnsTheNewlySetValue))
{
    auto& s = get_snake();

    auto const new_interval = 3;
    
    s.speed = new_interval;

    EXPECT_THAT(s.speed, Eq(new_interval));
}

TEST_THAT(Snake,
     WHAT(Speed),
     WHEN(WhenTryingToSetAValueLowerThanOne),
     THEN(SetsTheValueToOne))
{    
    auto& s = get_snake();

    s.speed = 0;

    EXPECT_THAT(s.speed, Eq(1));
}

} }
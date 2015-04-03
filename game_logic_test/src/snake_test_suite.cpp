#include "stdafx.hpp"

#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "snake_overflow/testing/fake_item.hpp"

namespace snake_overflow { namespace testing
{
    
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
     WHAT(Advance),
     WHEN(WhenTheHeadOfTheSnakeCollidesWithAnItem),
     THEN(LetsTheItemBePickedByTheSnake))
{
    auto i = make_item({{0, 0, 4}, block_face::front});

    auto& t = get_terrain();

    t.add_item(std::move(i));

    auto& s = get_snake();

    s.advance();

    EXPECT_THROW(s.advance(), item_picked_exception);
}

TEST_THAT(Snake,
     WHAT(Advance),
     WHEN(WhenTheHeadOfTheSnakeCollidesWithAPartOfItsBody),
     THEN(KillsTheSnake))
{
    auto& s = get_snake();

    s.grow(5);

    s.turn_right();

    s.advance();

    s.turn_right();

    s.advance();

    s.turn_right();

    s.advance();

    EXPECT_TRUE(s.is_dead);
}

TEST_THAT(Snake,
     WHAT(Advance),
     WHEN(WhenTheSnakeIsDead),
     THEN(Throws))
{
    auto& s = get_snake();

    s.is_dead.set();

    EXPECT_THROW(s.advance(), dead_snake_exception);
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

} }
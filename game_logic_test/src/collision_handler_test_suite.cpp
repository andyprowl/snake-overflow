#include "stdafx.hpp"

#include "snake_overflow/collision_handler.hpp"
#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "snake_overflow/testing/fake_item.hpp"

namespace snake_overflow { namespace testing
{
    
class CollisionHandler : public CubeTerrainGameFixture
{

protected:

    std::unique_ptr<item> make_item(util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    }

    // The collision handler is implicitly created as part of the game object.

};

TEST_THAT(CollisionHandler,
     WHAT(InternalEventHandlingLogic),
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

TEST_THAT(CollisionHandler,
     WHAT(InternalEventHandlingLogic),
     WHEN(WhenTheHeadOfTheSnakeCollidesWithAPartOfItsBody),
     THEN(TerminatesTheGame))
{
    auto& s = get_snake();

    s.grow(5);

    s.turn_right();

    s.advance();

    s.turn_right();

    s.advance();

    s.turn_right();

    s.advance();

    auto& g = get_game();

    EXPECT_TRUE(g.is_game_over);
}

} }
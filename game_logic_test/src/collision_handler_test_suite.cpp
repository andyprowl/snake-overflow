#include "stdafx.hpp"

#include "snake_overflow/collision_handler.hpp"
#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "snake_overflow/testing/fake_item.hpp"

namespace snake_overflow { namespace testing
{
    
class CollisionHandler : public CubeTerrainGameFixture
{

protected:

    virtual void SetUp() override
    {
        CubeTerrainGameFixture::SetUp();

        auto& g = get_game();

        this->handler = std::make_unique<collision_handler>(g);
    }

    std::unique_ptr<item> make_item(util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    }

protected:

    std::unique_ptr<collision_handler> handler;

};

TEST_THAT(CollisionHandler,
     WHAT(InternalEventHandlingLogic),
     WHEN(WhenTheSnakeCollidesWithAnItem),
     THEN(LetsTheItemBePickedByTheSnake))
{
    auto i = make_item({{0, 0, 4}, block_face::front});

    auto& t = get_terrain();

    t.add_item(std::move(i));

    auto& s = get_snake();

    s.advance();

    EXPECT_THROW(s.advance(), item_picked_exception);
}

} }
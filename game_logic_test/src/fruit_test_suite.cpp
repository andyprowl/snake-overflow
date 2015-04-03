#include "stdafx.hpp"

#include "snake_overflow/fruit.hpp"
#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "util/repeat.hpp"
#include <memory>

namespace snake_overflow { namespace testing
{

using ::testing::Contains;
using ::testing::Eq;
using ::testing::Ref;

class Fruit : public CubeTerrainGameFixture
{

protected:

    virtual void SetUp() override
    {
        CubeTerrainGameFixture::SetUp();

        auto& g = get_game();

        auto i = std::make_unique<fruit>(this->placement, 
                                         g,
                                         this->nutrition_value);

        this->f = i.get();

        auto& ground = get_terrain();

        ground.add_item(std::move(i));
    }

protected:

    int nutrition_value = 5;

    position placement = {{1, 0, 2}, block_face::front};

    fruit* f;

};

TEST_THAT(Fruit,
     WHAT(GetPosition),
     WHEN(Always),
     THEN(ReturnsThePositionPassedAtConstruction))
{
    EXPECT_THAT(this->f->get_position(), Eq(this->placement));
}

TEST_THAT(Fruit,
     WHAT(NutritionValue),
     WHEN(ImmediatelyAfterConstruction),
     THEN(HasTheValuePassedAtConstruction))
{
    EXPECT_THAT(this->f->get_nutrition_value(), Eq(this->nutrition_value));
}

TEST_THAT(Fruit,
     WHAT(Pick),
     WHEN(GivenAPickingSnake),
     THEN(MakesTheSnakeGrowByItsNutritionValue))
{
    auto& s = get_snake();

    this->f->pick(s);

    util::repeat(10, [&s] { s.advance(); });

    auto const expected_length = this->initial_snake_length + 
                                 this->nutrition_value;

    EXPECT_THAT(s.get_length(), Eq(expected_length));
}

TEST_THAT(Fruit,
     WHAT(Pick),
     WHEN(Always),
     THEN(RemovesTheItemFromTheTerrain))
{
    auto& s = get_snake();

    this->f->pick(s);

    auto& t = get_terrain();

    auto const b = t.get_block(placement.location);
    
    EXPECT_THAT(b.items.size(), Eq(0u));
}

TEST_THAT(Fruit,
     WHAT(Pick),
     WHEN(Always),
     THEN(AddsTheNutritionValueToTheCurrentScore))
{
    auto& s = get_snake();

    this->f->pick(s);

    auto& g = get_game();

    EXPECT_THAT(g.score, Eq(this->nutrition_value));
}

} }
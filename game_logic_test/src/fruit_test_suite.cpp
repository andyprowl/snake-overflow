#include "stdafx.hpp"

#include "snake_overflow/fruit.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "util/repeat.hpp"
#include <memory>

namespace snake_overflow
{

using ::testing::Contains;
using ::testing::Eq;
using ::testing::Ref;
using ::testing::Test;

class Fruit : public Test
{

protected:

    virtual void SetUp() override
    {
        auto builder = terrain_builder{this->habitat};

        builder.add_cube({0, 0, 0}, 10, "", {0, 0, 0, 255}, true);

        this->hero = std::make_unique<snake>(this->habitat, 
                                             this->initial_snake_footprint,
                                             this->initial_snake_length);

        this->f = std::make_unique<fruit>(this->placement, 
                                          this->nutrition_value);
    }

protected:

    int nutrition_value = 5;

    terrain habitat;
    
    int initial_snake_length = 3;

    footprint initial_snake_footprint = footprint{
        {0, 0, 0}, 
        {block_face::front, canonical_direction::positive_z()}};

    std::unique_ptr<snake> hero;

    position placement = {{3, 0, 4}, block_face::front};

    std::unique_ptr<fruit> f;

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
    EXPECT_THAT(this->f->nutrition_value, Eq(this->nutrition_value));
}

TEST_THAT(Fruit,
     WHAT(Pick),
     WHEN(GivenAPickingSnake),
     THEN(MakesTheSnakeGrowByItsNutritionValue))
{
    this->f->pick(*hero);

    util::repeat(10, [this] { this->hero->advance(); });

    auto const expected_length = this->initial_snake_length + 
                                 this->nutrition_value;

    EXPECT_THAT(this->hero->get_length(), Eq(expected_length));
}

}
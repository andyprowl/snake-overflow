#include "stdafx.hpp"

#include "snake_overflow/game.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Ref;
using ::testing::Test;

class Game : public Test
{

protected:

    virtual void SetUp() override
    {
        auto t = create_terrain();

        auto s = create_snake(*t);

        this->g = std::make_unique<game>(std::move(t), std::move(s));
    }

    std::unique_ptr<terrain> create_terrain()
    {
        auto t = std::make_unique<terrain>();

        this->habitat = t.get();

        auto builder = terrain_builder{*t};

        builder.add_cube(point::zero(), 4, "", rgba_color::white(), true);

        return t;
    }

    std::unique_ptr<snake> create_snake(terrain& habitat)
    {
        auto s = std::make_unique<snake>(
            habitat, 
            footprint{point::zero(), 
                      {block_face::front, canonical_direction::positive_z()}},
            3);

        this->hero = s.get();

        return s;
    }

protected:

    terrain* habitat = nullptr;

    snake* hero = nullptr;

    std::unique_ptr<game> g;

};

TEST_THAT(Game,
     WHAT(GetTerrain),
     WHEN(Always),
     THEN(ReturnsTheTerrainPassedAtConstruction))
{
    EXPECT_THAT(this->g->get_terrain(), Ref(*(this->habitat)));
}

TEST_THAT(Game,
     WHAT(GetSnake),
     WHEN(Always),
     THEN(ReturnsTheSnakePassedAtConstruction))
{
    EXPECT_THAT(this->g->get_snake(), Ref(*(this->hero)));
}

TEST_THAT(Game,
     WHAT(GetScore),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsZero))
{
    EXPECT_THAT(this->g->get_score(), Eq(0));
}

TEST_THAT(Game,
     WHAT(AddPoints),
     WHEN(GivenAnAmountOfPoints),
     THEN(AddsThatAmountToTheCurrentScore))
{
    this->g->add_points(3);
    EXPECT_THAT(this->g->get_score(), Eq(3));

    this->g->add_points(5);
    EXPECT_THAT(this->g->get_score(), Eq(8));

    this->g->add_points(-3);
    EXPECT_THAT(this->g->get_score(), Eq(5));
}

} }
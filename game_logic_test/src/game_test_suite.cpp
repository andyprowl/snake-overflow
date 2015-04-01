#include "stdafx.hpp"

#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Ref;

class Game : public CubeTerrainGameFixture
{
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

TEST_THAT(Game,
     WHAT(AddPoints),
     WHEN(GivenANegativeAmountOfPointsWhichWouldBringTheScoreBelowZero),
     THEN(SetsTheScoreToZero))
{
    this->g->add_points(3);
    EXPECT_THAT(this->g->get_score(), Eq(3));

    this->g->add_points(-8);
    EXPECT_THAT(this->g->get_score(), Eq(0));
}

TEST_THAT(Game,
     WHAT(AddPoints),
     WHEN(WhenTheGameIsOver),
     THEN(Throws))
{
    this->g->set_game_over();

    EXPECT_THROW(this->g->add_points(3), game_over_exception);
}

TEST_THAT(Game,
     WHAT(IsOver),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsFalse))
{
    EXPECT_FALSE(this->g->is_game_over());
}

TEST_THAT(Game,
     WHAT(SetGameOver),
     WHEN(Always),
     THEN(SetsTheGameOverFlag))
{
    this->g->set_game_over();

    EXPECT_TRUE(g->is_game_over());
}

} }
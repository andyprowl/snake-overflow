#include "stdafx.hpp"

#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "util/repeat.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Gt;
using ::testing::Ne;
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

    EXPECT_TRUE(this->g->is_game_over());
}

TEST_THAT(Game,
     WHAT(IsGamePaused),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsFalse))
{
    EXPECT_FALSE(this->g->is_game_paused());
}

TEST_THAT(Game,
     WHAT(ToogleGamePause),
     WHEN(WhenTheGameIsNotPaused),
     THEN(PausesTheGame))
{
    this->g->toggle_game_pause();

    EXPECT_TRUE(this->g->is_game_paused());
}

TEST_THAT(Game,
     WHAT(ToogleGamePause),
     WHEN(WhenTheGameIsPaused),
     THEN(UnpausesTheGame))
{
    this->g->toggle_game_pause();

    this->g->toggle_game_pause();

    EXPECT_FALSE(this->g->is_game_paused());
}

TEST_THAT(Game,
     WHAT(ToggleGamePause),
     WHEN(WhenTheGameIsOver),
     THEN(Throws))
{
    this->g->set_game_over();

    EXPECT_THROW(this->g->toggle_game_pause(), game_over_exception);
}

TEST_THAT(Game,
     WHAT(GetSnakeAdvancementInterval),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsANonNegativeValue))
{
    EXPECT_THAT(this->g->get_snake_advancement_interval(), Gt(0));
}

TEST_THAT(Game,
     WHAT(GetSnakeAdvancementInterval),
     WHEN(AfterSettingTheInterval),
     THEN(ReturnsTheNewlySetValue))
{
    auto const new_interval = 1337;
    
    this->g->set_snake_advancement_interval(new_interval);

    EXPECT_THAT(this->g->get_snake_advancement_interval(), Eq(new_interval));
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenTheGameIsPaused),
     THEN(DoesNotAdvanceTheSnake))
{
    auto& s = get_snake();

    auto const initial_footprint = s.get_trail_head().step;

    this->g->toggle_game_pause();

    this->g->update();

    EXPECT_THAT(s.get_trail_head().step, Eq(initial_footprint));
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenTheGameIsOver),
     THEN(DoesNotAdvanceTheSnake))
{
    auto& s = get_snake();

    auto const initial_footprint = s.get_trail_head().step;

    this->g->set_game_over();

    this->g->update();

    EXPECT_THAT(s.get_trail_head().step, Eq(initial_footprint));
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenCalledForTheNthTimeWithNEqualToTheSnakeAdvancementInterval),
     THEN(AdvancesTheSnake))
{
    auto& s = get_snake();

    auto const initial_footprint = s.get_trail_head().step;

    auto const interval = this->g->get_snake_advancement_interval();

    this->g->update();

    auto const next_footprint = s.get_trail_head().step;

    EXPECT_THAT(next_footprint, Ne(initial_footprint));

    util::repeat(interval - 1, [this] { this->g->update(); });

    EXPECT_THAT(s.get_trail_head().step, Eq(next_footprint));

    this->g->update();

    EXPECT_THAT(s.get_trail_head().step, Ne(next_footprint));
}

TEST_THAT(Game,
     WHAT(GetTerrainItemFillingInterval),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsANonNegativeValue))
{
    EXPECT_THAT(this->g->get_terrain_item_filling_interval(), Gt(0));
}

TEST_THAT(Game,
     WHAT(GetTerrainItemFillingInterval),
     WHEN(AfterSettingTheInterval),
     THEN(ReturnsTheNewlySetValue))
{
    auto const new_interval = 1337;
    
    this->g->set_terrain_item_filling_interval(new_interval);

    EXPECT_THAT(this->g->get_terrain_item_filling_interval(), Eq(new_interval));
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenCalledForTheNthTimeWithNEqualToTheItemGenerationInterval),
     THEN(LetsTheTerrainItemFillerGenerateItems))
{
    auto const interval = this->g->get_terrain_item_filling_interval();

    this->g->update();

    EXPECT_TRUE(this->terrain_filler->invoked);

    this->terrain_filler->invoked = false;

    util::repeat(interval - 1, [this] { this->g->update(); });

    EXPECT_FALSE(this->terrain_filler->invoked);

    this->g->update();

    EXPECT_TRUE(this->terrain_filler->invoked);
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenTheGameIsPaused),
     THEN(DoesNotFillTheTerrain))
{
    this->g->toggle_game_pause();

    this->g->update();

    EXPECT_FALSE(this->terrain_filler->invoked);
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenTheGameIsOver),
     THEN(DoesNotFillTheTerrain))
{
    this->g->set_game_over();

    this->g->update();

    EXPECT_FALSE(this->terrain_filler->invoked);
}

} }
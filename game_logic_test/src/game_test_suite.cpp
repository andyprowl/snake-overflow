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
     WHAT(Score),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToZero))
{
    EXPECT_THAT(this->g->score, Eq(0));
}

TEST_THAT(Game,
     WHAT(Score),
     WHEN(WhenIncrementedByAnAmountOfPoints),
     THEN(AddsThatAmountToTheCurrentScore))
{
    this->g->score += 3;
    EXPECT_THAT(this->g->score, Eq(3));

    this->g->score += 5;
    EXPECT_THAT(this->g->score, Eq(8));

    this->g->score += -3;
    EXPECT_THAT(this->g->score, Eq(5));
}

TEST_THAT(Game,
     WHAT(Score),
     WHEN(WhenSubtractingAnAmountOfPointsWhichWouldBringTheScoreBelowZero),
     THEN(SetsTheScoreToZero))
{
    this->g->score += 3;
    EXPECT_THAT(this->g->score, Eq(3));

    this->g->score -= 8;
    EXPECT_THAT(this->g->score, Eq(0));
}

TEST_THAT(Game,
     WHAT(Score),
     WHEN(WhenModifiedAndTheGameIsOver),
     THEN(Throws))
{
    this->g->is_game_over = true;

    EXPECT_THROW((this->g->score += 3), game_over_exception);
}

TEST_THAT(Game,
     WHAT(IsGameOver),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToFalse))
{
    EXPECT_FALSE(this->g->is_game_over);
}

TEST_THAT(Game,
     WHAT(IsGameOver),
     WHEN(IfTheGameIsNotOverAndTheValueIsSetToTrue),
     THEN(SetsTheGameOverFlag))
{
    this->g->is_game_over = true;

    EXPECT_TRUE(this->g->is_game_over);
}

TEST_THAT(Game,
     WHAT(IsGameOver),
     WHEN(IfTheGameIsOverAndTheValueIsSetToFalse),
     THEN(Throws))
{
    this->g->is_game_over = true;

    EXPECT_THROW((this->g->is_game_over = false), game_over_exception);
}

TEST_THAT(Game,
     WHAT(IsGameOver),
     WHEN(IfTheGameIsOverAndTheValueIsSetToTrue),
     THEN(DoesNothing))
{
    this->g->is_game_over = true;

    EXPECT_NO_THROW((this->g->is_game_over = true));
}

TEST_THAT(Game,
     WHAT(IsGamePaused),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToFalse))
{
    EXPECT_FALSE(this->g->is_game_paused);
}

TEST_THAT(Game,
     WHAT(ToogleGamePause),
     WHEN(WhenTheGameIsNotPaused),
     THEN(PausesTheGame))
{
    toggle_game_pause(*(this->g));

    EXPECT_TRUE(this->g->is_game_paused);
}

TEST_THAT(Game,
     WHAT(ToogleGamePause),
     WHEN(WhenTheGameIsPaused),
     THEN(UnpausesTheGame))
{
    this->g->is_game_paused = true;

    toggle_game_pause(*(this->g));

    EXPECT_FALSE(this->g->is_game_paused);
}

TEST_THAT(Game,
     WHAT(IsGameOver),
     WHEN(WhenAssignedAndTheGameIsOver),
     THEN(Throws))
{
    this->g->is_game_over = true;

    EXPECT_THROW(toggle_game_pause(*(this->g)), game_over_exception);
}

TEST_THAT(Game,
     WHAT(SnakeAdvancementInterval),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToANonNegativeValue))
{
    EXPECT_THAT(this->g->snake_advancement_interval, Gt(0));
}

TEST_THAT(Game,
     WHAT(SnakeAdvancementInterval),
     WHEN(AfterSettingAValueGreaterThanOne),
     THEN(ReturnsTheNewlySetValue))
{
    auto const new_interval = 1337;
    
    this->g->snake_advancement_interval = new_interval;

    EXPECT_THAT(this->g->snake_advancement_interval, Eq(new_interval));
}

TEST_THAT(Game,
     WHAT(SnakeAdvancementInterval),
     WHEN(WhenTryingToSetAValueLowerThanOne),
     THEN(SetsTheValueToOne))
{    
    this->g->snake_advancement_interval = 0;

    EXPECT_THAT(this->g->snake_advancement_interval, Eq(1));
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenTheGameIsPaused),
     THEN(DoesNotAdvanceTheSnake))
{
    auto& s = get_snake();

    auto const initial_footprint = s.get_trail_head().step;

    this->g->is_game_paused = true;

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

    this->g->is_game_over = true;

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

    auto const interval = this->g->snake_advancement_interval;

    this->g->update();

    auto const next_footprint = s.get_trail_head().step;

    EXPECT_THAT(next_footprint, Ne(initial_footprint));

    util::repeat(interval - 1, [this] { this->g->update(); });

    EXPECT_THAT(s.get_trail_head().step, Eq(next_footprint));

    this->g->update();

    EXPECT_THAT(s.get_trail_head().step, Ne(next_footprint));
}

TEST_THAT(Game,
     WHAT(TerrainItemFillingInterval),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToANonNegativeValue))
{
    EXPECT_THAT(this->g->terrain_filling_interval, Gt(0));
}

TEST_THAT(Game,
     WHAT(TerrainItemFillingInterval),
     WHEN(AfterSettingTheIntervalToAValueGreaterThanZero),
     THEN(EvaluatesToTheNewlySetValue))
{
    auto const new_interval = 1337;
    
    this->g->terrain_filling_interval = new_interval;

    EXPECT_THAT(this->g->terrain_filling_interval, Eq(new_interval));
}

TEST_THAT(Game,
     WHAT(TerrainItemFillingInterval),
     WHEN(WhenTryingToSetTheIntervalToAValueLowerThanOne),
     THEN(TheValueIsSetToOne))
{
    this->g->terrain_filling_interval = -1;

    EXPECT_THAT(this->g->terrain_filling_interval, Eq(1));
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenCalledForTheNthTimeWithNEqualToTheItemGenerationInterval),
     THEN(LetsTheTerrainItemFillerGenerateItems))
{
    auto const interval = this->g->terrain_filling_interval;

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
    this->g->is_game_paused = true;

    this->g->update();

    EXPECT_FALSE(this->terrain_filler->invoked);
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenTheGameIsOver),
     THEN(DoesNotFillTheTerrain))
{
    this->g->is_game_over = true;

    this->g->update();

    EXPECT_FALSE(this->terrain_filler->invoked);
}

} }
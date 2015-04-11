#include "stdafx.hpp"

#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "snake_overflow/testing/fake_item.hpp"
#include "util/repeat.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Gt;
using ::testing::Ne;
using ::testing::Ref;

class Game : public CubeTerrainGameFixture
{

protected:

    fake_item& add_new_item_to_terrain(util::value_ref<position> pos)
    {
        auto i = make_item(pos);

        auto& new_item = *i;

        get_terrain().add_item(std::move(i));

        return new_item;
    }

    std::unique_ptr<fake_item> make_item(util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    }

    void let_snake_bit_its_tail() const
    {
        auto& s = get_snake();

        s.grow(4);

        util::repeat(3, [this, &s] 
        {
            util::repeat(get_snake_update_interval(s), [this] 
            { 
                this->g->update(); 
            });

            s.turn_right();
        });

        this->g->update();
    }

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
    this->g->is_game_over.set();

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
     WHEN(IfTheGameIsNotOverAndTheValueIsSet),
     THEN(SetsTheGameOverFlag))
{
    this->g->is_game_over.set();

    EXPECT_TRUE(this->g->is_game_over);
}

TEST_THAT(Game,
     WHAT(IsGameOver),
     WHEN(IfTheGameIsOverAndTheValueIsSet),
     THEN(DoesNothing))
{
    this->g->is_game_over.set();
    
    EXPECT_TRUE(this->g->is_game_over);
    
    EXPECT_NO_THROW(this->g->is_game_over.set());
}

TEST_THAT(Game,
     WHAT(IsGameOver),
     WHEN(WhenTheSnakeIsDead),
     THEN(EvaluatesToTrue))
{
    this->hero->is_dead.set();

    EXPECT_TRUE(this->g->is_game_over);
}

TEST_THAT(Game,
     WHAT(IsGamePaused),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToFalse))
{
    EXPECT_FALSE(this->g->is_game_paused);
}

TEST_THAT(Game,
     WHAT(IsGameOver),
     WHEN(WhenSet),
     THEN(KillsTheSnake))
{
    this->g->is_game_over.set();

    EXPECT_TRUE(this->hero->is_dead);
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
    this->g->is_game_over.set();

    EXPECT_THROW(toggle_game_pause(*(this->g)), game_over_exception);
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenTheGameIsPaused),
     THEN(DoesNotAdvanceTheSnake))
{
    auto& body = get_snake_body();

    auto const initial_footprint = body.get_trail_head().step;

    this->g->is_game_paused = true;

    this->g->update();

    EXPECT_THAT(body.get_trail_head().step, Eq(initial_footprint));
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenTheGameIsOver),
     THEN(DoesNotAdvanceTheSnake))
{
    auto& body = get_snake_body();

    auto const initial_footprint = body.get_trail_head().step;

    this->g->is_game_over.set();

    this->g->update();

    EXPECT_THAT(body.get_trail_head().step, Eq(initial_footprint));
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
     WHEN(Always),
     THEN(ShortensTheLifetimeOfAllItemsOnTheTerrain))
{
    auto& i1 = add_new_item_to_terrain({{0, 0, 0}, block_face::front});
    auto& i2 = add_new_item_to_terrain({{0, 0, 1}, block_face::front});
    auto& i3 = add_new_item_to_terrain({{0, 0, 2}, block_face::front});

    this->g->update();

    EXPECT_THAT(i1.item_age, Eq(1));
    EXPECT_THAT(i2.item_age, Eq(1));
    EXPECT_THAT(i3.item_age, Eq(1));
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
    this->g->is_game_over.set();

    this->g->update();

    EXPECT_FALSE(this->terrain_filler->invoked);
}

TEST_THAT(Game,
     WHAT(Update),
     WHEN(WhenTheGameEnds),
     THEN(AddsTheGameScoreToTheRankings))
{
    auto const points = 42;

    this->g->score = points;

    let_snake_bit_its_tail();

    auto const scores = this->rankings.get_rankings();

    ASSERT_THAT(scores.size(), Eq(1u));

    EXPECT_THAT(scores.back().points, Eq(points));
}

} }
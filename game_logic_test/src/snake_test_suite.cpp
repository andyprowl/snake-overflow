#include "stdafx.hpp"

#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "snake_overflow/testing/fake_item.hpp"
#include "snake_overflow/testing/fake_spell.hpp"
#include "util/repeat.hpp"

namespace snake_overflow { namespace testing
{
    
using ::testing::Contains;
using ::testing::Eq;
using ::testing::Gt;
using ::testing::Ne;

class Snake : public CubeTerrainGameFixture
{

protected:

    std::unique_ptr<item> make_item(util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    }

    std::unique_ptr<spell> make_spell(
        std::vector<spell*>* last_affecting_spells = nullptr)
    {
        return std::make_unique<fake_spell>(last_affecting_spells);
    }

    // The collision handler is implicitly created as part of the game object.

};

TEST_THAT(Snake,
     WHAT(Skin),
     WHEN(ImmediatelyAfterConstruction),
     THEN(HoldsTheNameOfTheSkinPassedAtConstruction))
{
    auto& s = get_snake();

    EXPECT_THAT(s.skin, Eq(this->snake_skin));
}

TEST_THAT(Snake,
     WHAT(GetName),
     WHEN(Always),
     THEN(ReturnsTheNamePassedAtConstruction))
{
    auto& s = get_snake();

    EXPECT_THAT(s.get_name(), Eq(this->snake_name));
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenTheHeadOfTheSnakeCollidesWithAnItem),
     THEN(LetsTheItemBePickedByTheSnake))
{
    auto i = make_item({{0, 0, 4}, block_face::front});

    auto& t = get_terrain();

    t.add_item(std::move(i));

    auto& s = get_snake();

    s.get_body().advance();

    EXPECT_THROW(s.get_body().advance(), item_picked_exception);
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenTheHeadOfTheSnakeCollidesWithAPartOfItsBody),
     THEN(KillsTheSnake))
{
    auto& s = get_snake();

    auto const update_interval = get_snake_update_interval(s);

    s.grow(5);

    s.turn_right();

    util::repeat(update_interval, [&s] { s.update(); });

    s.turn_right();

    util::repeat(update_interval, [&s] { s.update(); });

    s.turn_right();

    s.update();

    EXPECT_TRUE(s.is_dead);
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenTheSnakeIsDead),
     THEN(DoesNothing))
{
    auto& s = get_snake();

    auto& b = s.get_body();

    auto old_head = b.get_trail_head().step;

    s.is_dead.set();

    EXPECT_NO_THROW([&s]
    {
        auto const update_interval = get_snake_update_interval(s);

        util::repeat(update_interval, [&s] { s.update(); });
    });

    EXPECT_THAT(b.get_trail_head().step, Eq(old_head));
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
     WHAT(TurnLeft),
     WHEN(WhenInvokedMoreThanOnceBeforeAnUpdate),
     THEN(WillOnlyCauseOneTurnLeftDuringTheNextUpdate))
{
    auto& s = get_snake();

    s.turn_left();

    s.turn_left();

    s.turn_left();

    s.update();

    auto& b = s.get_body();

    EXPECT_THAT(b.get_direction(), Eq(canonical_direction::positive_y()));
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
     WHAT(TurnRight),
     WHEN(WhenInvokedMoreThanOnceBeforeAnUpdate),
     THEN(WillOnlyCauseOneTurnRightDuringTheNextUpdate))
{
    auto& s = get_snake();

    s.turn_right();

    s.turn_right();

    s.turn_right();

    s.update();

    auto& b = s.get_body();

    EXPECT_THAT(b.get_direction(), Eq(canonical_direction::positive_x()));
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

TEST_THAT(Snake,
     WHAT(InvulnerabilityBonus),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToFalse))
{
    auto& s = get_snake();

    EXPECT_FALSE(s.invulnerability_bonus);
}

TEST_THAT(Snake,
     WHAT(InvulnerabilityBonus),
     WHEN(AfterSettingItsValue),
     THEN(EvaluatesToTheNewlySetValue))
{
    auto& s = get_snake();

    s.invulnerability_bonus = true;

    EXPECT_TRUE(s.invulnerability_bonus);
}

TEST_THAT(Snake,
     WHAT(InvulnerabilityBonus),
     WHEN(WhenSettingItsValueAfterTheSnakeHasDied),
     THEN(Throws))
{
    auto& s = get_snake();

    s.is_dead.set();

    EXPECT_THROW((s.invulnerability_bonus = true), dead_snake_exception);
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenCalledForTheNthTimeWithNEqualToTheUpdateInterval),
     THEN(UpdatesTheBody))
{
    auto& s = get_snake();

    auto& body = get_snake_body();

    auto const initial_footprint = body.get_trail_head().step;

    auto const interval = get_snake_update_interval(s);

    s.update();

    auto const next_footprint = body.get_trail_head().step;

    EXPECT_THAT(next_footprint, Ne(initial_footprint));

    util::repeat(interval - 1, [&s] { s.update(); });

    EXPECT_THAT(body.get_trail_head().step, Eq(next_footprint));

    s.update();

    EXPECT_THAT(body.get_trail_head().step, Ne(next_footprint));
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(WhenTheSnakeBitesItselfButHasAPositiveInvulnerabilityBonus),
     THEN(DoesNotKillTheSnake))
{
    auto& s = get_snake();

    s.grow(5);

    s.turn_right();

    s.update();

    s.turn_right();

    s.update();

    s.turn_right();

    s.invulnerability_bonus = true;

    s.update();

    EXPECT_FALSE(s.is_dead);
}

TEST_THAT(Snake,
     WHAT(Speed),
     WHEN(ImmediatelyAfterConstruction),
     THEN(EvaluatesToANonNegativeValue))
{
    auto& s = get_snake();

    EXPECT_THAT(s.speed, Gt(0));
}

TEST_THAT(Snake,
     WHAT(Speed),
     WHEN(AfterSettingAValueGreaterThanOneButLessThanTheMaximum),
     THEN(ReturnsTheNewlySetValue))
{
    auto& s = get_snake();

    auto const new_interval = 3;
    
    s.speed = new_interval;

    EXPECT_THAT(s.speed, Eq(new_interval));
}

TEST_THAT(Snake,
     WHAT(Speed),
     WHEN(WhenTryingToSetAValueLowerThanOne),
     THEN(SetsTheValueToOne))
{    
    auto& s = get_snake();

    s.speed = 0;

    EXPECT_THAT(s.speed, Eq(1));
}

TEST_THAT(Snake,
     WHAT(AddSpell),
     WHEN(GivenASpellThatDoesNotAffectTheSnakeYet),
     THEN(MakesTheSnakeAffectedByThatSpell))
{
    auto& s = get_snake();

    auto sp = make_spell();

    auto& added_spell = *sp;

    s.add_spell(std::move(sp));

    auto const spells = s.get_all_spells();

    EXPECT_THAT(spells.size(), Eq(1u));
    EXPECT_THAT(spells, Contains(&added_spell));
}

TEST_THAT(Snake,
     WHAT(RemoveSpell),
     WHEN(GivenASpellThatIsAffectingTheSnake),
     THEN(RemovesThatSpellFromTheSetOfPendingSpells))
{
    auto& s = get_snake();

    auto sp = make_spell();

    auto& added_spell = *sp;

    s.add_spell(std::move(sp));

    s.remove_spell(added_spell);

    auto const spells = s.get_all_spells();
    EXPECT_TRUE(spells.empty());
}

TEST_THAT(Snake,
     WHAT(GetAllSpells),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsAnEmptyCollection))
{
    auto& s = get_snake();
    
    auto const spells = s.get_all_spells();

    EXPECT_TRUE(spells.empty());
}

TEST_THAT(Snake,
     WHAT(GetAllSpells),
     WHEN(AfterAddingAFewSpellS),
     THEN(ReturnsAContainerContainingAllThoseSpellsInOrderOfAddition))
{
    auto& s = get_snake();
    
    auto s1 = make_spell();
    auto s1_ptr = s1.get();
    s.add_spell(std::move(s1));

    auto s2 = make_spell();
    auto s2_ptr = s2.get();
    s.add_spell(std::move(s2));

    auto s3 = make_spell();
    auto s3_ptr = s3.get();
    s.add_spell(std::move(s3));

    auto const spells = s.get_all_spells();

    ASSERT_THAT(spells.size(), Eq(3u));

    EXPECT_THAT(spells[0], Eq(s1_ptr));
    EXPECT_THAT(spells[1], Eq(s2_ptr));
    EXPECT_THAT(spells[2], Eq(s3_ptr));
}

TEST_THAT(Snake,
     WHAT(Update),
     WHEN(Always),
     THEN(LetsAllThePendingSpellsAffectTheSnake))
{
    auto& s = get_snake();
 
    auto affecting_spells = std::vector<spell*>{};

    auto s1 = make_spell(&affecting_spells);
    auto const s1_ptr = s1.get();
    s.add_spell(std::move(s1));

    auto s2 = make_spell(&affecting_spells);
    auto const s2_ptr = s2.get();
    s.add_spell(std::move(s2));

    s.update();

    EXPECT_THAT(affecting_spells.size(), Eq(2u));
    EXPECT_THAT(affecting_spells, Contains(s1_ptr));
    EXPECT_THAT(affecting_spells, Contains(s2_ptr));
}

} }
#include "stdafx.hpp"

#include "snake_overflow/frenzy_spell.hpp"
#include "snake_overflow/speed_booster.hpp"
#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "util/repeat.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Ne;
    
class SpeedBooster : public CubeTerrainGameFixture
{
    
protected:

    virtual void SetUp() override
    {
        CubeTerrainGameFixture::SetUp();

        auto& g = get_game();

        auto i = std::make_unique<speed_booster>(this->placement, 
                                                 g,
                                                 this->lifetime,
                                                 this->spell_duration);

        this->booster = i.get();

        auto& ground = get_terrain();

        ground.add_item(std::move(i));
    }

protected:

    int spell_duration = 10;

    position placement = {{1, 0, 2}, block_face::front};

    int lifetime = 50;

    speed_booster* booster;

};

TEST_THAT(SpeedBooster,
     WHAT(GetPosition),
     WHEN(Always),
     THEN(ReturnsThePositionPassedAtConstruction))
{
    EXPECT_THAT(this->booster->get_position(), Eq(this->placement));
}

TEST_THAT(SpeedBooster,
     WHAT(Pick),
     WHEN(GivenAPickingSnake),
     THEN(AddsAFrenzySpellToTheSnakeWithDurationPassedAtConstruction))
{
    auto& s = get_snake();

    this->booster->pick(s);
    
    auto const all_spells = s.get_all_spells();

    ASSERT_THAT(all_spells.size(), Eq(1u));

    auto sp = dynamic_cast<frenzy_spell*>(all_spells[0]);

    ASSERT_THAT(sp, Ne(nullptr));

    EXPECT_THAT(sp->get_duration(), Eq(this->spell_duration));
}

TEST_THAT(SpeedBooster,
     WHAT(Pick),
     WHEN(Always),
     THEN(RemovesTheItemFromTheTerrain))
{
    auto& s = get_snake();

    this->booster->pick(s);

    auto& t = get_terrain();

    auto const b = t.get_block(placement.location);
    
    EXPECT_THAT(b.items.size(), Eq(0u));
}

TEST_THAT(SpeedBooster,
     WHAT(Lifetime),
     WHEN(AfterShorteningIt),
     THEN(EvaluatesToAValueLowerThanThePreviousOneUnit))
{
    this->booster->lifetime.shorten();

    EXPECT_THAT(this->booster->lifetime, Eq(this->lifetime - 1)); 
}

TEST_THAT(SpeedBooster,
     WHAT(Lifetime),
     WHEN(WhenShorteningDownToZero),
     THEN(RemovesTheDietPillFromTheTerrain))
{
    util::repeat(this->lifetime, [this] { this->booster->lifetime.shorten(); });

    auto& ground = get_terrain();

    EXPECT_THAT(ground.get_num_of_items(), Eq(0));
}

TEST_THAT(SpeedBooster,
     WHAT(Age),
     WHEN(Always),
     THEN(ShortensTheLifetime))
{
    this->booster->age();

    EXPECT_THAT(this->booster->lifetime, Eq(this->lifetime - 1)); 
}

} }
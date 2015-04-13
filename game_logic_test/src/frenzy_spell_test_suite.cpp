#include "stdafx.hpp"

#include "snake_overflow/frenzy_spell.hpp"
#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"
#include "util/repeat.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
    
class FrenzySpell : public CubeTerrainGameFixture
{

protected:

    virtual void SetUp() override
    {
        CubeTerrainGameFixture::SetUp();

        this->the_spell = std::make_unique<frenzy_spell>(this->lifetime);
    }

protected:

    int lifetime = 5;

    std::unique_ptr<frenzy_spell> the_spell;

};

TEST_THAT(FrenzySpell,
     WHAT(Affect),
     WHEN(GivenASnakeToWhichTheSpellWasAdded),
     THEN(IncrementsItSpeedForANumberOfUpdatesEqualToTheLifetimeOfTheSpell))
{
    auto& s = get_snake();

    auto added_spell = this->the_spell.get();

    s.add_spell(std::move(this->the_spell));

    auto const initial_speed = s.speed;

    util::repeat(this->lifetime - 1, [added_spell, initial_speed, &s]
    {
        added_spell->affect(s);
        EXPECT_THAT(s.speed, Eq(initial_speed + 1));
    });

    added_spell->affect(s);
    EXPECT_THAT(s.speed, Eq(initial_speed));
}

TEST_THAT(FrenzySpell, 
     WHAT(Affect),
     WHEN(WhenTheLifetimeOfTheSpellReachesZero),
     THEN(RemovesSelfFromTheSnake))
{
    auto& s = get_snake();

    auto added_spell = this->the_spell.get();

    s.add_spell(std::move(this->the_spell));

    util::repeat(this->lifetime, [added_spell, &s]
    {
        added_spell->affect(s);
    });

    auto const spells = s.get_all_spells();

    EXPECT_TRUE(spells.empty());
}

} }
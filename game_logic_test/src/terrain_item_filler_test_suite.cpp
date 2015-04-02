#include "stdafx.hpp"

#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/load_driven_terrain_item_filler.hpp"
#include "snake_overflow/testing/fake_item.hpp"
#include "snake_overflow/testing/item_spawner_spy.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::AllOf;
using ::testing::Eq;
using ::testing::Ge;
using ::testing::Gt;
using ::testing::Le;
using ::testing::Lt;
using ::testing::Test;

class LoadDrivenTerrainItemFilter : public Test
{

protected:

    virtual void SetUp() override
    {
        auto s = std::make_unique<item_spawner_spy>(this->ground);

        this->spying_spawner = s.get();

        this->filler = std::make_unique<load_driven_terrain_item_filler>(
            std::move(s));
    }

    std::unique_ptr<item> make_item(util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    }

    void create_cube(util::value_ref<point> origin, int const side_length)
    {
        auto builder = terrain_builder{this->ground};

        builder.add_cube(origin, side_length, "", rgba_color::white(), true);
    }

protected:
    
    terrain ground;

    item_spawner_spy* spying_spawner = nullptr;

    std::unique_ptr<load_driven_terrain_item_filler> filler;

};

TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(GetMinimumLoadFactor),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsZero))
{
    EXPECT_THAT(this->filler->get_minimum_load_factor(), Eq(0.0));
}

TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(GetMinimumLoadFactor),
     WHEN(AfterSuccessfullyResettingTheMinimumLoad),
     THEN(ReturnsTheNewlySetMinimumLoad))
{
    auto const new_minimum = 0.02;

    this->filler->set_minimum_load_factor(new_minimum);

    EXPECT_THAT(this->filler->get_minimum_load_factor(), Eq(new_minimum));
}

TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(SetMinimumLoadFactor),
     WHEN(WhenTheGivenFactorIsLowerThanZeroPercent),
     THEN(Throws))
{
    EXPECT_THROW(this->filler->set_minimum_load_factor(-0.1), 
                 bad_load_factor_range_exception);
}

TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(SetMinimumLoadFactor),
     WHEN(WhenTheGivenFactorIsGreaterThanTheMaximum),
     THEN(Throws))
{
    auto const max_factor = this->filler->get_maximum_load_factor();

    EXPECT_THROW(this->filler->set_minimum_load_factor(max_factor + 0.01), 
                 bad_load_factor_range_exception);
}

TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(GetMaximumLoadFactor),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsANonNegativeNumberLowerThanFiftyPercent))
{
    EXPECT_THAT(this->filler->get_maximum_load_factor(), 
                AllOf(Gt(0.0), Lt(0.50)));
}

TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(GetMaximumLoadFactor),
     WHEN(AfterSuccessfullyResettingTheMaximumLoad),
     THEN(ReturnsTheNewlySetMaximumLoad))
{
    auto const new_maximum = 0.15;

    this->filler->set_maximum_load_factor(new_maximum);

    EXPECT_THAT(this->filler->get_maximum_load_factor(), Eq(new_maximum));
}

TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(SetMaximumLoadFactor),
     WHEN(WhenTheGivenFactorIsGreaterThanFiftyPercent),
     THEN(Throws))
{
    EXPECT_THROW(this->filler->set_maximum_load_factor(0.51), 
                 bad_load_factor_range_exception);
}

TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(SetMaximumLoadFactor),
     WHEN(WhenTheGivenFactorIsLowerThanTheMinimum),
     THEN(Throws))
{
    auto const min_factor = 0.1;

    this->filler->set_minimum_load_factor(min_factor);

    EXPECT_THROW(this->filler->set_maximum_load_factor(min_factor - 0.01), 
                 bad_load_factor_range_exception);
}

TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(FillTerrain),
     WHEN(WhenTheNumberOfItemsInTheTerrainExceedsTheMaximumLoadFactor),
     THEN(DoesNotSpawnAnyItem))
{
    create_cube({0, 0, 0}, 5);

    this->filler->set_maximum_load_factor(0.01);

    this->ground.add_item(make_item({{0, 0, 0}, block_face::front}));
    this->ground.add_item(make_item({{0, 0, 1}, block_face::front}));
    this->ground.add_item(make_item({{0, 0, 2}, block_face::front}));
    this->ground.add_item(make_item({{0, 0, 3}, block_face::front}));

    this->filler->fill_terrain();
    
    EXPECT_THAT(this->spying_spawner->num_of_last_spawned_items, Eq(0));
}

// This is more of an integration test, since it relies on non-deterministic
// behavior.
TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(FillTerrain),
     WHEN(WhenTheNumberOfItemsInTheTerrainIsBelowTheMinimumLoadFactor),
     THEN(AddsEnoughItemsToBringTheLoadFactorBetweenMinimumAndMaximum))
{
    create_cube({0, 0, 0}, 5);

    this->filler->set_maximum_load_factor(0.04);

    this->filler->set_minimum_load_factor(0.02);

    this->filler->fill_terrain();

    EXPECT_THAT(this->spying_spawner->num_of_last_spawned_items, Ge(3));
    
    EXPECT_THAT(this->spying_spawner->num_of_last_spawned_items, Le(6));
}

// This is more of an integration test, since it relies on non-deterministic
// behavior.
TEST_THAT(LoadDrivenTerrainItemFilter,
     WHAT(FillTerrain),
     WHEN(WhenTheNumberOfItemsInTheTerrainIsInTheAllowedLoadFactorRange),
     THEN(SpawnsANumberOfItemsThatWillNotExceedTheMinimumAndMaximum))
{
    create_cube({0, 0, 0}, 5);

    this->ground.add_item(make_item({{0, 0, 0}, block_face::front}));
    this->ground.add_item(make_item({{0, 0, 1}, block_face::front}));
    this->ground.add_item(make_item({{0, 0, 2}, block_face::front}));
    this->ground.add_item(make_item({{0, 0, 3}, block_face::front}));

    this->filler->set_maximum_load_factor(0.04);

    this->filler->set_minimum_load_factor(0.02);

    this->filler->fill_terrain();

    EXPECT_THAT(this->spying_spawner->num_of_last_spawned_items, Ge(0));
    
    EXPECT_THAT(this->spying_spawner->num_of_last_spawned_items, Le(2));
}

} }
#include "stdafx.hpp"

#include "snake_overflow/probabilistic_item_spawner.hpp"
#include "snake_overflow/random_item_position_picker.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/testing/fake_item.hpp"
#include "snake_overflow/testing/item_position_picker_mock.hpp"
#include <memory>

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Gt;
using ::testing::Invoke;
using ::testing::Return;
using ::testing::Test;

class ProbabilisticItemSpawner : public Test
{

protected:

    virtual void SetUp() override
    {
        auto builder = terrain_builder{this->ground};

        builder.add_cube({0, 0, 0}, 5, "", rgba_color::white(), true);

        auto pp = std::make_unique<item_position_picker_mock>();

        ON_CALL(*pp, pick_item_position()).WillByDefault(Invoke([this]
        {
            return this->random_picker->pick_item_position();
        }));

        this->position_picker = pp.get();

        this->spawner = std::make_unique<probabilistic_item_spawner>(
            this->ground, 
            std::move(pp));

        this->random_picker = std::make_unique<random_item_position_picker>(
            this->ground);
    }

protected:

    terrain ground;

    item_position_picker_mock* position_picker = nullptr;

    std::unique_ptr<random_item_position_picker> random_picker;

    std::unique_ptr<probabilistic_item_spawner> spawner;

};

TEST_THAT(ProbabilisticItemSpawner,
     WHAT(RegisterFactoryFunction),
     WHEN(GivenAProbabiltyThatGivesMoreThanAHundredWhenSummedToTheExistingOnes),
     THEN(Throws))
{
    auto factory = [] (util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    };

    this->spawner->register_item_factory(factory, 40);

    EXPECT_THROW(this->spawner->register_item_factory(factory, 61),
                 bad_factory_probability_distribution_exception);
}

TEST_THAT(ProbabilisticItemSpawner,
     WHAT(Spawn),
     WHEN(WhenTheSumOfRegisteredFactoryProbabilitiesDoesNotSumUpToOneHundred),
     THEN(Throws))
{
    auto factory = [] (util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    };

    this->spawner->register_item_factory(factory, 40);

    EXPECT_THROW(this->spawner->spawn(42),
                 bad_factory_probability_distribution_exception);
}

TEST_THAT(ProbabilisticItemSpawner,
     WHAT(Spawn),
     WHEN(GivenANumberOfItemsToSpawnAfterAtLeastOneFactoryHasBeenRegistered),
     THEN(SpawnsThatNumberOfItems))
{
    auto factory = [] (util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    };

    this->spawner->register_item_factory(factory, 100);

    auto const num_of_items = 5;

    this->spawner->spawn(num_of_items);

    EXPECT_THAT(this->ground.get_num_of_items(), Eq(num_of_items));
}

TEST_THAT(ProbabilisticItemSpawner,
     WHAT(Spawn),
     WHEN(WhenThePositionPickerReturnsAPositionThatIsAlreadyOccupied),
     THEN(PicksADifferentPositionAndStillSpawnsTheDesiredNumberOfItems))
{
    auto factory = [] (util::value_ref<position> pos)
    {
        return std::make_unique<fake_item>(pos);
    };

    this->spawner->register_item_factory(factory, 100);

    EXPECT_CALL(*this->position_picker, pick_item_position())
                .WillOnce(Return(position{{0, 0, 0}, block_face::front}))
                .WillOnce(Return(position{{0, 0, 0}, block_face::front}))
                .WillOnce(Return(position{{0, 0, 0}, block_face::front}))
                .WillOnce(Return(position{{0, 0, 0}, block_face::front}))
                .WillRepeatedly(Invoke([this]
    {
        return this->random_picker->pick_item_position();
    }));

    auto const num_of_items = 5;

    this->spawner->spawn(num_of_items);

    EXPECT_THAT(this->ground.get_num_of_items(), Eq(num_of_items));
}

// This is more of an integration test, since it relies on non-deterministic
// behavior.
TEST_THAT(ProbabilisticItemSpawner,
     WHAT(Spawn),
     WHEN(GivenWeightsThatSumUpToOneHundredForAllFactoryFunctions),
     THEN(PicksTheCorrespondingFactoryWithAppropriateRelativeFrequency))
{
    auto count1 = 0;
    auto f1 = [&count1] (util::value_ref<position> pos)
    {
        ++count1;
        return std::make_unique<fake_item>(pos);
    };

    auto count2 = 0;
    auto f2 = [&count2] (util::value_ref<position> pos)
    {
        ++count2;
        return std::make_unique<fake_item>(pos);
    };

    this->spawner->register_item_factory(f1, 20);
    this->spawner->register_item_factory(f2, 80);

    auto const num_of_items = 100;

    this->spawner->spawn(num_of_items);

    EXPECT_THAT(this->ground.get_num_of_items(), Eq(num_of_items));

    EXPECT_THAT(count2, Gt(count1));
}

} }
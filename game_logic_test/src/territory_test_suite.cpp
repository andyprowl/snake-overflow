#include "stdafx.hpp"

#include "snake_overflow/game_logic/territory.hpp"
#include "snake_overflow/game_logic/block.hpp"

namespace snake_overflow { namespace game_logic { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class Territory : public Test
{

protected:

    territory t;

};

TEST_THAT(Territory,
     WHAT(GetBlocks),
     WHEN(ImmediatelyAfterDefaultConstruction),
     THEN(ReturnsAnEmptyCollectionOfBlocks))
{
    auto const blocks = t.get_blocks();

    EXPECT_TRUE(blocks.empty());
}

TEST_THAT(Territory,
     WHAT(AddBlock),
     WHEN(GivenABlockThatIsNotAlreadyPartOfTheTerritory),
     THEN(AddsTheBlockToTheTerritory))
{
    auto const b = block{{0, 1, 2}};

    t.add_block(b);

    auto const blocks = t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));

    EXPECT_THAT(blocks[0], Eq(b));
}

TEST_THAT(Territory,
     WHAT(AddBlock),
     WHEN(GivenABlockThatIsAlreadyPartOfTheTerritory),
     THEN(DoesNotAddThatBlockAgain))
{
    auto const b = block{{0, 1, 2}};

    t.add_block(b);

    t.add_block(b);

    auto const blocks = t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));
}

} } }
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

    territory s;

};

TEST_THAT(Territory,
     WHAT(GetBlocks),
     WHEN(ImmediatelyAfterDefaultConstruction),
     THEN(ReturnsASingleBlockAtTheWorldOrigin))
{
    auto const blocks = s.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));

    EXPECT_THAT(blocks[0].x, Eq(0));
    EXPECT_THAT(blocks[0].y, Eq(0));
    EXPECT_THAT(blocks[0].z, Eq(0));
}

} } }
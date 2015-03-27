#include "stdafx.hpp"

#include "snake_overflow/game_logic/territory.hpp"
#include "snake_overflow/game_logic/block.hpp"

namespace snake_overflow { namespace game_logic { namespace testing
{

using ::testing::Test;

class Territory : public Test
{

protected:

    territory s;

};

TEST_THAT(Territory,
     WHAT(GetBlocks),
     WHEN(ImmediatelyAfterDefaultConstruction),
     THEN(ReturnsAnEmptyCollection))
{
    EXPECT_TRUE(s.get_blocks().empty());
}

} } }
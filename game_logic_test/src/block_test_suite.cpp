#include "stdafx.hpp"

#include "snake_overflow/game_logic/block.hpp"

namespace snake_overflow { namespace game_logic { namespace testing
{

using ::testing::Test;

class Block : public Test
{
};

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithTheSameCoordinates),
     THEN(ReturnsTrue))
{
    auto const b1 = block{42, 1337, 1729};

    auto const b2 = block{42, 1337, 1729};

    EXPECT_TRUE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentCoordinates),
     THEN(ReturnsFalse))
{
    auto const b1 = block{42, 1337, 1729};

    auto const b2 = block{42, 0, 1729};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(InequalityComparisonOperator),
     WHEN(GivenTwoBlocksWithTheSameCoordinates),
     THEN(ReturnsFalse))
{
    auto const b1 = block{42, 1337, 1729};

    auto const b2 = block{42, 1337, 1729};

    EXPECT_FALSE(b1 != b2);
}

TEST_THAT(Block,
     WHAT(InequalityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentCoordinates),
     THEN(ReturnsTrue))
{
    auto const b1 = block{42, 1337, 1729};

    auto const b2 = block{42, 0, 1729};

    EXPECT_TRUE(b1 != b2);
}

} } }
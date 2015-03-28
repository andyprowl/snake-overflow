#include "stdafx.hpp"

#include "snake_overflow/game_logic/block.hpp"

namespace snake_overflow { namespace game_logic { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class Block : public Test
{
};

TEST_THAT(Block,
     WHAT(GetOrigin),
     WHEN(Always),
     THEN(ReturnsTheOriginPassedAtConstruction))
{
    auto const origin = point{42, 1337, -1729};

    auto const b = block{origin};

    EXPECT_THAT(b.get_origin(), Eq(origin));
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithTheSameOrigin),
     THEN(ReturnsTrue))
{
    auto const b1 = block{{42, 1337, 1729}};

    auto const b2 = block{{42, 1337, 1729}};

    EXPECT_TRUE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentOrigin),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 1337, 1729}};

    auto const b2 = block{{42, 0, 1729}};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(InequalityComparisonOperator),
     WHEN(GivenTwoBlocksWithTheSameOrigin),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 1337, 1729}};

    auto const b2 = block{{42, 1337, 1729}};

    EXPECT_FALSE(b1 != b2);
}

TEST_THAT(Block,
     WHAT(InequalityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentOrigin),
     THEN(ReturnsTrue))
{
    auto const b1 = block{{42, 1337, 1729}};

    auto const b2 = block{{42, 0, 1729}};
}

} } }
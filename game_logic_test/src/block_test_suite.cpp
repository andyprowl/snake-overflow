#include "stdafx.hpp"

#include "snake_overflow/block.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class Block : public Test
{
};

TEST_THAT(Block,
     WHAT(Constructor),
     WHEN(Always),
     THEN(StoresTheValuePassedForTheOrigin))
{
    auto const origin = point{42, 1337, -1729};

    auto const b = block{origin, "texture.jpg"};

    EXPECT_THAT(b.origin, Eq(origin));
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithTheSameOrigin),
     THEN(ReturnsTrue))
{
    auto const b1 = block{{42, 1337, 1729}, "texture.jpg"};

    auto const b2 = block{{42, 1337, 1729}, "texture.jpg"};

    EXPECT_TRUE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentOrigin),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 1337, 1729}, "texture.jpg"};

    auto const b2 = block{{42, 0, 1729}, "texture.jpg"};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(InequalityComparisonOperator),
     WHEN(GivenTwoBlocksWithTheSameOrigin),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 1337, 1729}, "texture.jpg"};

    auto const b2 = block{{42, 1337, 1729}, "texture.jpg"};

    EXPECT_FALSE(b1 != b2);
}

TEST_THAT(Block,
     WHAT(InequalityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentOrigin),
     THEN(ReturnsTrue))
{
    auto const b1 = block{{42, 1337, 1729}, "texture.jpg"};

    auto const b2 = block{{42, 0, 1729}, "texture.jpg"};

    EXPECT_TRUE(b1 != b2);
}

} }
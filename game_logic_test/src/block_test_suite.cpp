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

    auto const b = block{origin, "texture.jpg", {0, 0, 0, 255}, true};

    EXPECT_THAT(b.origin, Eq(origin));
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithIdenticalData),
     THEN(ReturnsTrue))
{
    auto const b1 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    auto const b2 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    EXPECT_TRUE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentOrigin),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    auto const b2 = block{{42, 0, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentTextures),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 1337, 1729}, 
                          "texture1.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    auto const b2 = block{{42, 1337, 1729}, 
                          "texture2.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentColors),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    auto const b2 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 255, 255}, 
                          true};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentSolidity),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    auto const b2 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          false};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(InequalityComparisonOperator),
     WHEN(GivenTwoBlocksWithIdenticalData),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    auto const b2 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    EXPECT_FALSE(b1 != b2);
}

TEST_THAT(Block,
     WHAT(InequalityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentOrigin),
     THEN(ReturnsTrue))
{
    auto const b1 = block{{42, 1337, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    auto const b2 = block{{42, 0, 1729}, 
                          "texture.jpg", 
                          {0, 0, 0, 255}, 
                          true};

    EXPECT_TRUE(b1 != b2);
}

TEST_THAT(Block,
     WHAT(IsBlockVisible),
     WHEN(GivenABlockWithAColorWhoseAlphaComponentIsGreaterThanZero),
     THEN(ReturnsTrue))
{
    auto const b = block{{42, 1337, 1729}, 
                         "texture.jpg", 
                         {0, 0, 0, 255}, 
                         true};

    EXPECT_TRUE(is_block_visible(b));
}

TEST_THAT(Block,
     WHAT(IsBlockVisible),
     WHEN(GivenABlockWithAColorWhoseAlphaComponentIsNotGreaterThanZero),
     THEN(ReturnsTrue))
{
    auto const b = block{{42, 1337, 1729}, 
                         "texture.jpg", 
                         {0, 0, 0, 0}, 
                         true};

    EXPECT_FALSE(is_block_visible(b));
}

} }
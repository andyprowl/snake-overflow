#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/testing/fake_item.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class Block : public Test
{

protected:

    terrain ground;

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
    auto const b1 = block{{42, 6, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    auto const b2 = block{{42, 6, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    EXPECT_TRUE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentOrigin),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 6, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    auto const b2 = block{{42, 0, 1337}, "texture.jpg", {0, 0, 0, 255}, true};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentTextures),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, 6, 1729}, "texture1.jpg", {0, 0, 0, 255}, true};

    auto const b2 = block{{42, 6, 1729}, "texture2.jpg", {0, 0, 0, 255}, true};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentColors),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, -6, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    auto const b2 = block{{42, -6, 1729}, "texture.jpg", {0, 0, 1, 255}, true};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentSolidity),
     THEN(ReturnsFalse))
{
    auto const b1 = block{{42, -1, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    auto const b2 = block{{42, -1, 1729}, "texture.jpg", {0, 0, 0, 255}, false};

    EXPECT_FALSE(b1 == b2);
}

TEST_THAT(Block,
     WHAT(EqualityComparisonOperator),
     WHEN(GivenTwoBlocksWithDifferentItems),
     THEN(ReturnsFalse))
{
    auto b1 = block{{42, 1337, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    fake_item f1{{{0, 0, 0}, block_face::front}};

    b1.items.push_back(&f1);

    auto b2 = block{{42, 1337, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    fake_item f2{{{0, 1, 0}, block_face::front}};

    b2.items.push_back(&f2);

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
    auto const b1 = block{{42, -42, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    auto const b2 = block{{42, 0, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    EXPECT_TRUE(b1 != b2);
}

TEST_THAT(Block,
     WHAT(IsBlockOpaque),
     WHEN(GivenABlockWithAColorWhoseAlphaComponentHasMaximumValue),
     THEN(ReturnsTrue))
{
    auto const b = block{{42, 1337, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    EXPECT_TRUE(is_block_opaque(b));
}

TEST_THAT(Block,
     WHAT(IsBlockOpaque),
     WHEN(GivenABlockWithAColorWhoseAlphaComponentDoesNotHaveMaximumValue),
     THEN(ReturnsFalse))
{
    auto const b = block{{42, 1337, 1729}, "texture.jpg", {0, 0, 0, 0}, true};

    EXPECT_FALSE(is_block_opaque(b));
}

TEST_THAT(Block,
     WHAT(IsBlockTranslucent),
     WHEN(GivenABlockWithAColorWhoseAlphaComponentDoesNotHaveMaximumValue),
     THEN(ReturnsTrue))
{
    auto const b = block{{42, 1337, 1729}, "texture.jpg", {0, 0, 0, 128}, true};

    EXPECT_TRUE(is_block_translucent(b));
}

TEST_THAT(Block,
     WHAT(IsBlockTranslucent),
     WHEN(GivenABlockWithAColorWhoseAlphaComponentHasMaximumValue),
     THEN(ReturnsFalse))
{
    auto const b = block{{42, 1337, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    EXPECT_FALSE(is_block_translucent(b));
}

TEST_THAT(Block,
     WHAT(IsBlockTransparent),
     WHEN(GivenABlockWithAColorWhoseAlphaComponentIsZero),
     THEN(ReturnsTrue))
{
    auto const b = block{{42, 1337, 1729}, "texture.jpg", {0, 0, 0, 0}, true};

    EXPECT_TRUE(is_block_transparent(b));
}

TEST_THAT(Block,
     WHAT(IsBlockTransparent),
     WHEN(GivenABlockWithAColorWhoseAlphaComponentIsGreaterThanZero),
     THEN(ReturnsFalse))
{
    auto const b = block{{42, 1337, 1729}, "texture.jpg", {0, 0, 0, 255}, true};

    EXPECT_FALSE(is_block_transparent(b));
}

} }
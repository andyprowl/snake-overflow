#include "stdafx.hpp"

#include "snake_overflow/serialization/block_type_list_tokenizing_reader.hpp"
#include "snake_overflow/serialization/block_type.hpp"
#include <sstream>

namespace snake_overflow { namespace serialization { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class BlockTypeListTokenizingReader : public Test
{

protected:

    block_type_list_tokenizing_reader reader;

};

TEST_THAT(BlockTypeListTokenizingReader,
     WHAT(FromStream),
     WHEN(GivenAContentThatDoesNotStartWithTheProperToken),
     THEN(Throws))
{
    auto const content = "1: grass4.jpg;   255, 172,0,255; S\n"
                         "2: water3.jpg;  15, 33,255,128; N\n"
                         "3: ice1.jpg; 0,   0,37, 0; S\n\n"
                         "END BLOCKS";

    auto ss = std::stringstream{content};

    EXPECT_THROW(this->reader.from_stream(ss), bad_block_type_list_exception);
}

TEST_THAT(BlockTypeListTokenizingReader,
     WHAT(FromStream),
     WHEN(GivenAContentThatDoesNotEndWithTheProperToken),
     THEN(Throws))
{
    auto const content = "BEGIN BLOCK TYPES\n\n"
                         "1: grass4.jpg; 255,172,0,255; S\n"
                         "2: water3.jpg; 15,33,255,128; N\n"
                         "3: ice1.jpg; 0,0,37,0; S\n\n";

    auto ss = std::stringstream{content};

    EXPECT_THROW(this->reader.from_stream(ss), bad_block_type_list_exception);
}

TEST_THAT(BlockTypeListTokenizingReader,
     WHAT(FromStream),
     WHEN(GivenAContentWhereBlockTypeSymbolsContainMoreThanOneCharacter),
     THEN(ReturnsAMapWithThePropertiesOfTheListedBlockTypes))
{
    auto const content = "BEGIN BLOCK TYPES\n\n"
                         "1: grass4.jpg; 255,172, 0,   255; S\n"
                         "22: water3.jpg; 15, 33,255, 128; N\n"
                         "3: ice1.jpg; 0, 0,    37,0; S\n\n"
                         "END BLOCK TYPES";

    auto ss = std::stringstream{content};

    EXPECT_THROW(this->reader.from_stream(ss), bad_block_type_list_exception);
}

TEST_THAT(BlockTypeListTokenizingReader,
     WHAT(FromStream),
     WHEN(GivenAProperlyEncodedListOfBlockTypes),
     THEN(ReturnsAMapWithThePropertiesOfTheListedBlockTypes))
{
    auto const content = "BEGIN BLOCK TYPES\n\n"
                         "1: grass4.jpg; 255,172, 0,   255; S\n"
                         "2: water3.jpg; 15, 33,255, 128; N\n"
                         "3: ice1.jpg; 0, 0,    37,0; S\n\n"
                         "END BLOCK TYPES";

    auto ss = std::stringstream{content};

    auto blocks = this->reader.from_stream(ss);

    EXPECT_THAT(blocks.size(), Eq(3u));

    EXPECT_TRUE(blocks.at('1').is_solid);
    EXPECT_THAT(blocks.at('1').color, Eq(rgba_color{255, 172, 0, 255}));
    EXPECT_THAT(blocks.at('1').texture, Eq("grass4.jpg"));
    
    EXPECT_FALSE(blocks.at('2').is_solid);
    EXPECT_THAT(blocks.at('2').color, Eq(rgba_color{15, 33, 255, 128}));
    EXPECT_THAT(blocks.at('2').texture, Eq("water3.jpg"));

    EXPECT_TRUE(blocks.at('3').is_solid);
    EXPECT_THAT(blocks.at('3').color, Eq(rgba_color{0, 0, 37, 0}));
    EXPECT_THAT(blocks.at('3').texture, Eq("ice1.jpg"));
}

} } }
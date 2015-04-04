#include "stdafx.hpp"

#include "snake_overflow/serialization/terrain_layer_tokenizing_reader.hpp"

namespace snake_overflow { namespace serialization { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class TerrainLayerTokenizingReader : public Test
{

protected:

    terrain_layer_tokenizing_reader reader;

};

TEST_THAT(TerrainLayerTokenizingReader,
     WHAT(FromStream),
     WHEN(GivenAContentThatDoesNotStartWithTheProperToken),
     THEN(Throws))
{
    auto const content = "\n"
                         "    1 1 1 \n"
                         "  1 2 2 2 1 1 \n"
                         "3 2 1 \n"
                         "\n"
                         "END LAYER\n";

    auto ss = std::istringstream{content};

    EXPECT_THROW(this->reader.from_stream(ss), bad_layer_exception);
}

TEST_THAT(TerrainLayerTokenizingReader,
     WHAT(FromStream),
     WHEN(GivenAContentThatDoesNotEndWithTheProperToken),
     THEN(Throws))
{
    auto const content = "BEGIN LAYER { NORMAL:+z; DEPTH:0; ORIGIN:-50,-50 }\n"
                         "\n"
                         "    1 1 1 \n"
                         "  1 2 2 2 1 1 \n"
                         "3 2 1 \n"
                         "\n";

    auto ss = std::istringstream{content};

    EXPECT_THROW(this->reader.from_stream(ss), bad_layer_exception);
}

TEST_THAT(TerrainLayerTokenizingReader, 
     WHAT(FromStream),
     WHEN(GivenAContentForALayerWithPositiveZAsNormal),
     THEN(CorrectlyParsesTheEncodedBlockLocationsAndTypes))
{
    auto const content = "BEGIN LAYER { NORMAL:+z; HEIGHT:5; ORIGIN:-50,-50 }\n"
                         "   \n"
                         "    1 1 1        \n"
                         "  1 2 2   2 1 1 \n"
                         "\n"
                         "3 2 1 \n"
                         "\n"
                         "END LAYER\n";

    auto ss = std::istringstream{content};

    auto result = this->reader.from_stream(ss);

    EXPECT_THAT(result.size(), Eq(12u));

    EXPECT_THAT(result.at({-48, -51, 5}), Eq('1'));
    EXPECT_THAT(result.at({-47, -51, 5}), Eq('1'));
    EXPECT_THAT(result.at({-46, -51, 5}), Eq('1'));

    EXPECT_THAT(result.at({-49, -52, 5}), Eq('1'));
    EXPECT_THAT(result.at({-48, -52, 5}), Eq('2'));
    EXPECT_THAT(result.at({-47, -52, 5}), Eq('2'));
    EXPECT_THAT(result.at({-45, -52, 5}), Eq('2'));
    EXPECT_THAT(result.at({-44, -52, 5}), Eq('1'));
    EXPECT_THAT(result.at({-43, -52, 5}), Eq('1'));

    EXPECT_THAT(result.at({-50, -54, 5}), Eq('3'));
    EXPECT_THAT(result.at({-49, -54, 5}), Eq('2'));
    EXPECT_THAT(result.at({-48, -54, 5}), Eq('1'));
}

TEST_THAT(TerrainLayerTokenizingReader, 
     WHAT(FromStream),
     WHEN(GivenAContentForALayerWithNegativeYAsNormal),
     THEN(CorrectlyParsesTheEncodedBlockLocationsAndTypes))
{
    auto const content = "BEGIN LAYER { NORMAL:-y; HEIGHT:2; ORIGIN:0,0 }\n"
                         "   \n"
                         "    1 1 1        \n"
                         "  1 2 2   2 1 1 \n"
                         "\n"
                         "3 2 1 \n"
                         "\n"
                         "END LAYER\n";

    auto ss = std::istringstream{content};

    auto result = this->reader.from_stream(ss);

    EXPECT_THAT(result.size(), Eq(12u));

    EXPECT_THAT(result.at({2, -2, -1}), Eq('1'));
    EXPECT_THAT(result.at({3, -2, -1}), Eq('1'));
    EXPECT_THAT(result.at({4, -2, -1}), Eq('1'));

    EXPECT_THAT(result.at({1, -2, -2}), Eq('1'));
    EXPECT_THAT(result.at({2, -2, -2}), Eq('2'));
    EXPECT_THAT(result.at({3, -2, -2}), Eq('2'));
    EXPECT_THAT(result.at({5, -2, -2}), Eq('2'));
    EXPECT_THAT(result.at({6, -2, -2}), Eq('1'));
    EXPECT_THAT(result.at({7, -2, -2}), Eq('1'));

    EXPECT_THAT(result.at({0, -2, -4}), Eq('3'));
    EXPECT_THAT(result.at({1, -2, -4}), Eq('2'));
    EXPECT_THAT(result.at({2, -2, -4}), Eq('1'));
}

} } }
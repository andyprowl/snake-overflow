#include "stdafx.hpp"

#include "snake_overflow/serialization/terrain_layer_set_delegating_reader.hpp"
#include "snake_overflow/serialization/terrain_layer_tokenizing_reader.hpp"

namespace snake_overflow { namespace serialization { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class TerrainLayerSetDelegatingReader : public Test
{

protected:

    terrain_layer_tokenizing_reader layer_reader;

    terrain_layer_set_delegating_reader reader{layer_reader};

};

TEST_THAT(TerrainLayerSetDelegatingReader,
     WHAT(FromStream),
     WHEN(Always),
     THEN(DelegatesReadingOfLayersToLayerReaderAndAssemblesTheResults))
{
    auto const content = "BEGIN LAYER { NORMAL:-y; HEIGHT:2; ORIGIN:0,0 }\n"
                         "   \n"
                         "  111      \n"
                         "\n"
                         "END LAYER\n"
                         "\n"
                         "BEGIN LAYER { NORMAL:-y; HEIGHT:3; ORIGIN:0,0 }\n"
                         " 234  \n"
                         "\n"
                         "  3      \n"
                         "END LAYER\n"
                         "\n"
                         "BEGIN LAYER { NORMAL:-y; HEIGHT:4; ORIGIN:0,0 }\n"
                         "\n"
                         "\n"
                         "\n"
                         "        8\n"
                         "END LAYER\n";

    auto ss = std::stringstream{content};

    auto result = this->reader.from_stream(ss);

    EXPECT_THAT(result.size(), Eq(8u));

    EXPECT_THAT(result.at({2, -2, -1}), Eq('1'));
    EXPECT_THAT(result.at({3, -2, -1}), Eq('1'));
    EXPECT_THAT(result.at({4, -2, -1}), Eq('1'));

    EXPECT_THAT(result.at({1, -3, 0}), Eq('2'));
    EXPECT_THAT(result.at({2, -3, 0}), Eq('3'));
    EXPECT_THAT(result.at({3, -3, 0}), Eq('4'));
    EXPECT_THAT(result.at({2, -3, -2}), Eq('3'));

    EXPECT_THAT(result.at({8, -4, -3}), Eq('8'));
}

} } }
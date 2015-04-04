#include "stdafx.hpp"

#include "snake_overflow/serialization/terrain_delegating_reader.hpp"
#include "snake_overflow/serialization/block_type_list_tokenizing_reader.hpp"
#include "snake_overflow/serialization/terrain_layer_tokenizing_reader.hpp"
#include "snake_overflow/serialization/terrain_layer_set_delegating_reader.hpp"
#include "snake_overflow/serialization/testing/block_type_list_reader_mock.hpp"
#include "snake_overflow/serialization/testing/terrain_layer_set_reader_mock.hpp"

namespace snake_overflow { namespace serialization { namespace testing
{

using ::testing::Eq;
using ::testing::Ref;
using ::testing::Return;
using ::testing::Test;

class TerrainDelegatingReader : public Test
{

protected:

    block_type_list_reader_mock block_type_reader;
    
    terrain_layer_set_reader_mock layer_set_reader;

    terrain_delegating_reader reader{block_type_reader, layer_set_reader};

};

TEST_THAT(TerrainDelegatingReader,
     WHAT(FromStream),
     WHEN(GivenAStreamThatEncodesATerrain),
     THEN(DelegatesParsingToTheSubParsersAndAssemblesTheResult))
{
    auto const s = "SOME TERRAIN REPRESENTATION";

    auto ss = std::stringstream{s};

    auto const block_types = std::unordered_map<char, block_type>{
        {'x', {"ice.jpg", rgba_color::white(), true}},
        {'y', {"fire.jpg", rgba_color::red(), true}},
        {'o', {"water.jpg", rgba_color::blue(), false}}};

    EXPECT_CALL(this->block_type_reader, from_stream(Ref(ss)))
                .WillOnce(Return(block_types));

    auto const block_map = std::unordered_map<point, char>{
        {{0, 0, 0}, 'x'},
        {{0, 0, 1}, 'y'},
        {{0, 1, 0}, 'o'},
        {{1, 0, 0}, 'x'}};

    EXPECT_CALL(this->layer_set_reader, from_stream(Ref(ss)))
                .WillOnce(Return(block_map));

    auto const result = this->reader.from_stream(ss);

    auto const blocks = result->get_all_blocks();

    EXPECT_THAT(blocks.size(), Eq(4u));

    EXPECT_THAT(result->get_block({0, 0, 0}).texture, Eq("ice.jpg"));
    EXPECT_THAT(result->get_block({0, 0, 1}).texture, Eq("fire.jpg"));
    EXPECT_THAT(result->get_block({0, 1, 0}).texture, Eq("water.jpg"));
    EXPECT_THAT(result->get_block({1, 0, 0}).texture, Eq("ice.jpg"));

    EXPECT_THAT(result->get_block({0, 0, 0}).color, Eq(rgba_color::white()));
    EXPECT_THAT(result->get_block({0, 0, 1}).color, Eq(rgba_color::red()));
    EXPECT_THAT(result->get_block({0, 1, 0}).color, Eq(rgba_color::blue()));
    EXPECT_THAT(result->get_block({1, 0, 0}).color, Eq(rgba_color::white()));

    EXPECT_TRUE(result->get_block({0, 0, 0}).is_solid);
    EXPECT_TRUE(result->get_block({0, 0, 1}).is_solid);
    EXPECT_FALSE(result->get_block({0, 1, 0}).is_solid);
    EXPECT_TRUE(result->get_block({1, 0, 0}).is_solid);
}

TEST_THAT(TerrainDelegatingReader,
     WHAT(FromStream),
     WHEN(GivenAStreamThatEncodesATerrainWithSeveralLayers),
     THEN(ReturnsACorrectlyParsedTerrain))
{
    auto const content = "BEGIN BLOCK TYPES\n"
                         "\n"
                         "1: grass4.jpg;   255, 172,0,255; S\n"
                         "2: water3.jpg;  15, 33,255,128; N\n"
                         "3: ice1.jpg; 0,   0,37, 192; S\n"
                         "4: lava1.jpg; 255, 0, 0, 255; S\n"
                         "\n"
                         "END BLOCK TYPES\n"
                         "\n"
                         "BEGIN LAYER { NORMAL:-y; HEIGHT:2; ORIGIN:0,0 }\n"
                         "   \n"
                         "    1 1 1       \n"
                         "\n"
                         "END LAYER\n"
                         "\n"
                         "BEGIN LAYER { NORMAL:-y; HEIGHT:3; ORIGIN:0,0 }\n"
                         "  2 3 4   \n"
                         "\n"
                         "    3       \n"
                         "END LAYER\n"
                         "\n"
                         "BEGIN LAYER { NORMAL:-y; HEIGHT:4; ORIGIN:0,0 }\n"
                         "\n"
                         "\n"
                         "\n"
                         "                4 \n"
                         "END LAYER\n";

    auto ss = std::istringstream{content};

    auto block_type_reader = block_type_list_tokenizing_reader{};
    auto layer_reader = terrain_layer_tokenizing_reader{};
    auto layer_set_reader = terrain_layer_set_delegating_reader{layer_reader};
    auto real_reader = terrain_delegating_reader{block_type_reader, layer_set_reader};

    auto const result = real_reader.from_stream(ss);

    EXPECT_THAT(result->get_all_blocks().size(), Eq(8u));

    EXPECT_THAT(result->get_block({2, -2, -1}).texture, Eq("grass4.jpg"));
    EXPECT_TRUE(result->get_block({2, -2, -1}).is_solid);
    EXPECT_THAT(result->get_block({2, -2, -1}).color, 
                Eq(rgba_color{255, 172,0,255}));
}

} } }
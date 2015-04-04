#pragma once

#include "snake_overflow/serialization/terrain_layer_set_reader.hpp"

namespace snake_overflow { namespace serialization { namespace testing
{

class terrain_layer_set_reader_strict_mock : public terrain_layer_set_reader
{

public:

    MOCK_METHOD1(from_stream, 
                 std::unordered_map<point, char>(std::istream&));

};

using terrain_layer_set_reader_mock = 
      ::testing::NiceMock<terrain_layer_set_reader_strict_mock>;

} } }
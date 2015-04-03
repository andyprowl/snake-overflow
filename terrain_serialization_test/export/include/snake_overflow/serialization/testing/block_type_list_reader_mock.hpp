#pragma once

#include "snake_overflow/serialization/block_type_list_reader.hpp"

namespace snake_overflow { namespace serialization
{

class block_type_list_reader_strict_mock : public block_type_list_reader
{

public:

    MOCK_METHOD1(from_stream, 
                 std::unordered_map<char, block_type>(std::istream&));

};

using block_type_list_reader_mock = 
      ::testing::NiceMock<block_type_list_reader_strict_mock>;

} }
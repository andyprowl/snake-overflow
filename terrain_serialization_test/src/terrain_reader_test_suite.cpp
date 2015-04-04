#include "stdafx.hpp"

#include "snake_overflow/serialization/terrain_reader.hpp"
#include "snake_overflow/serialization/testing/block_type_list_reader_mock.hpp"

namespace snake_overflow { namespace serialization { namespace testing
{

using ::testing::Test;

class TerrainReader : public Test
{

protected:

    block_type_list_reader_mock block_type_reader;

    terrain_reader reader{block_type_reader};

};

} } }
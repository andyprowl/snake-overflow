#include "stdafx.hpp"

#include "snake_overflow/serialization/terrain_reader.hpp"

namespace snake_overflow { namespace serialization
{

terrain_reader::terrain_reader(block_type_list_reader& block_type_reader)
    : block_type_reader{block_type_reader}
{
};

} }
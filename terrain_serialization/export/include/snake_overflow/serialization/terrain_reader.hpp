#pragma once

namespace snake_overflow { namespace serialization
{

class block_type_list_reader;

class terrain_reader
{

public:

    terrain_reader(block_type_list_reader& block_type_reader);

private:

    block_type_list_reader& block_type_reader;

};

} }
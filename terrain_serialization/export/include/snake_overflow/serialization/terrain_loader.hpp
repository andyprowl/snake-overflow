#pragma once

#include "snake_overflow/serialization/block_type_list_tokenizing_reader.hpp"
#include "snake_overflow/serialization/terrain_delegating_reader.hpp"
#include "snake_overflow/serialization/terrain_layer_tokenizing_reader.hpp"
#include "snake_overflow/serialization/terrain_layer_set_delegating_reader.hpp"
#include "snake_overflow/terrain.hpp"
#include <boost/filesystem/path.hpp>

namespace snake_overflow { namespace serialization 
{

class terrain_loader
{

public:

    std::unique_ptr<terrain> load_terrain(
        util::value_ref<boost::filesystem::path> filepath);

private:

    block_type_list_tokenizing_reader block_map_reader;
    
    terrain_layer_tokenizing_reader layer_reader;
    
    terrain_layer_set_delegating_reader layer_set_reader{layer_reader};

    terrain_delegating_reader reader{block_map_reader, layer_set_reader};

};

} }
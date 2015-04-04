#include "stdafx.hpp"

#include "snake_overflow/serialization/block_type_list_reader.hpp"
#include "snake_overflow/serialization/terrain_layer_set_reader.hpp"
#include "snake_overflow/serialization/terrain_delegating_reader.hpp"
#include <string>

namespace snake_overflow { namespace serialization
{

terrain_delegating_reader::terrain_delegating_reader(
    block_type_list_reader& block_type_reader,
    terrain_layer_set_reader& layer_set_reader)
    : block_type_reader{block_type_reader}
    , layer_set_reader{layer_set_reader}
{
}

std::unique_ptr<terrain> terrain_delegating_reader::from_stream(
    std::istream& is)
{
    auto const block_types = this->block_type_reader.from_stream(is);

    auto empty_line = std::string{};
    std::getline(is, empty_line);

    auto const block_map = this->layer_set_reader.from_stream(is);

    return create_terrain(block_map, block_types);
}

std::unique_ptr<terrain> terrain_delegating_reader::create_terrain(
    util::value_ref<block_map> block_map,
    util::value_ref<block_type_map> block_types) const
{
    auto t = std::make_unique<terrain>();

    for (auto const entry : block_map)
    {
        auto const type = block_types.at(entry.second);

        auto const b = block{entry.first, 
                             type.texture, 
                             type.color, 
                             type.is_solid};

        t->add_block(b);
    }

    return t;
}

} }
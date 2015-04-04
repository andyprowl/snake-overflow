#pragma once

#include "snake_overflow/serialization/terrain_reader.hpp"
#include "snake_overflow/point.hpp"
#include "util/value_ref.hpp"
#include <unordered_map>

namespace snake_overflow { namespace serialization
{

class block_type_list_reader;
class terrain_layer_set_reader;

struct block_type;

class terrain_delegating_reader : public terrain_reader
{

public:

    terrain_delegating_reader(block_type_list_reader& block_type_reader,
                              terrain_layer_set_reader& layer_set_reader);

    virtual std::unique_ptr<terrain> from_stream(std::istream& is) override;

private:

    using block_map = std::unordered_map<point, char>;

    using block_type_map = std::unordered_map<char, block_type>;

    std::unique_ptr<terrain> create_terrain(
        util::value_ref<block_map> block_map,
        util::value_ref<block_type_map> block_types) const;

private:

    block_type_list_reader& block_type_reader;

    terrain_layer_set_reader& layer_set_reader;

};

} }
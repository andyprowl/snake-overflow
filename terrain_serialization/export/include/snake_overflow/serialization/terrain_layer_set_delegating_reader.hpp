#pragma once

#include "snake_overflow/serialization/terrain_layer_set_reader.hpp"

namespace snake_overflow { namespace serialization
{

class terrain_layer_reader;

class terrain_layer_set_delegating_reader : public terrain_layer_set_reader
{

public:

    terrain_layer_set_delegating_reader(terrain_layer_reader& layer_reader);

    std::unordered_map<point, char> from_stream(std::istream& is);

private:

    void eat_empty_line(std::istream& is) const;

private:

    terrain_layer_reader& layer_reader;

};

} }
#include "stdafx.hpp"

#include "snake_overflow/serialization/terrain_layer_set_delegating_reader.hpp"
#include "snake_overflow/serialization/terrain_layer_reader.hpp"
#include <cassert>
#include <iterator>
#include <string>

namespace snake_overflow { namespace serialization
{

terrain_layer_set_delegating_reader::terrain_layer_set_delegating_reader(
    terrain_layer_reader& layer_reader)
    : layer_reader{layer_reader}
{
}

std::unordered_map<point, char> 
    terrain_layer_set_delegating_reader::from_stream(std::istream& is)
{
    auto result = std::unordered_map<point, char>{};

    while (is)
    {
        auto partial_result = this->layer_reader.from_stream(is);

        result.insert(std::make_move_iterator(std::begin(partial_result)),
                      std::make_move_iterator(std::end(partial_result)));

        eat_empty_line(is);
    }

    return result;
}

void terrain_layer_set_delegating_reader::eat_empty_line(std::istream& is) const
{
    auto empty_line = std::string{};
    
    std::getline(is, empty_line);
    
    assert(empty_line.empty());
}

} }
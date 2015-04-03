#pragma once

#include "snake_overflow/point.hpp"
#include <istream>
#include <stdexcept>
#include <unordered_map>

namespace snake_overflow { namespace serialization
{

class bad_layer_exception : public virtual std::exception
{
};

class terrain_layer_reader
{

public:

    virtual ~terrain_layer_reader() = default;

    virtual std::unordered_map<point, char> from_stream(std::istream& is) = 0;

};

} }
#pragma once

#include "snake_overflow/terrain.hpp"
#include <istream>
#include <memory>

namespace snake_overflow { namespace serialization
{

class terrain_reader
{

public:

    virtual ~terrain_reader() = default;

    virtual std::unique_ptr<terrain> from_stream(std::istream& is) = 0;

};

} }
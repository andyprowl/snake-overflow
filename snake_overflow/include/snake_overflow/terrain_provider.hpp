#pragma once

#include "util/value_ref.hpp"
#include <memory>
#include <string>

namespace snake_overflow
{

class terrain;

class terrain_provider
{

public:

    virtual ~terrain_provider() = default;

    virtual std::unique_ptr<terrain> create_terrain(
        util::value_ref<std::string> name) = 0;

};

}
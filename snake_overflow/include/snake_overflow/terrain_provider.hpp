#pragma once

#include <memory>
#include <string>

namespace snake_overflow
{

class terrain;

class terrain_provider
{

public:

    std::unique_ptr<terrain> create_terrain(std::string const& name);

};

}
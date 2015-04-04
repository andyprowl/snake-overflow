#pragma once

#include "snake_overflow/terrain_provider.hpp"

namespace snake_overflow
{

class default_terrain_provider : public terrain_provider
{

public:

    virtual std::unique_ptr<terrain> create_terrain(
        util::value_ref<std::string> name) override;

};

}
#include "stdafx.hpp"

#include "snake_overflow/serialization/terrain_loader.hpp"
#include <fstream>

namespace snake_overflow { namespace serialization
{

std::unique_ptr<terrain> terrain_loader::load_terrain(
    util::value_ref<boost::filesystem::path> filepath)
{
    auto fs = std::ifstream{filepath.string()};

    auto t = this->reader.from_stream(fs);

    t->sort_for_rendering();

    return t;
}

} }
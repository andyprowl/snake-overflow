#pragma once

#include "snake_overflow/game_map.hpp"
#include "snake_overflow/serialization/terrain_loader.hpp"
#include <memory>
#include <unordered_map>

namespace snake_overflow
{

class game_map_repository
{

public:

    game_map_repository();

    game_map& get_map(util::value_ref<std::string> name) const;

    boost::filesystem::path get_asset_directory() const;

    void load_all_maps_in_directory(
        util::value_ref<boost::filesystem::path> p);

    void load_map(util::value_ref<boost::filesystem::path> p);

private:

    serialization::terrain_loader loader;

    std::unordered_map<std::string, std::unique_ptr<game_map>> maps;

};

}
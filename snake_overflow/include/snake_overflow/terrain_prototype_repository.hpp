#pragma once

#include "snake_overflow/terrain_provider.hpp"
#include "snake_overflow/serialization/terrain_loader.hpp"
#include <memory>
#include <unordered_map>

namespace snake_overflow
{

class terrain_prototype_repository : public terrain_provider
{

public:

    terrain_prototype_repository();

    virtual std::unique_ptr<terrain> create_terrain(
        util::value_ref<std::string> name) override;

    boost::filesystem::path get_asset_directory() const;

    void load_all_terrains_in_directory(
        util::value_ref<boost::filesystem::path> p);

    void load_terrain(util::value_ref<boost::filesystem::path> p);

private:

    using terrain_map = 
          std::unordered_map<std::string, std::unique_ptr<terrain>>;

private:

    serialization::terrain_loader loader;

    terrain_map terrain_prototypes;

};

}
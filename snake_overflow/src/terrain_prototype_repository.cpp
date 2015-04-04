#include "stdafx.hpp"

#include "snake_overflow/terrain_prototype_repository.hpp"
#include "snake_overflow/serialization/terrain_loader.hpp"

namespace snake_overflow
{

terrain_prototype_repository::terrain_prototype_repository()
{
    auto const p = get_asset_directory();
    
    load_all_terrains_in_directory(p);
}

std::unique_ptr<terrain> terrain_prototype_repository::create_terrain(
    util::value_ref<std::string> name)
{
    return this->terrain_prototypes.at(name)->clone();
}

boost::filesystem::path 
    terrain_prototype_repository::get_asset_directory() const
{
    return {"../../assets/maps"};
}

void terrain_prototype_repository::load_all_terrains_in_directory(
    util::value_ref<boost::filesystem::path> p)
{
    using boost::filesystem::directory_iterator;

    for (auto const entry : boost::make_iterator_range(directory_iterator{p}, 
                                                       directory_iterator{}))
    {
        auto const p = entry.path();

        if (p.extension() == ".som")
        {
            load_terrain(p);
        }
    }
}

void terrain_prototype_repository::load_terrain(
    util::value_ref<boost::filesystem::path> p)
{
    auto terrain_name = p.filename().string();
    
    auto t = this->loader.load_terrain(p.string());

    this->terrain_prototypes.emplace(std::move(terrain_name), std::move(t));
}

}
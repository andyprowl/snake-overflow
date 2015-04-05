#include "stdafx.hpp"

#include "snake_overflow/game_map_repository.hpp"
#include "snake_overflow/serialization/terrain_loader.hpp"

namespace snake_overflow
{

game_map_repository::game_map_repository()
{
    auto const p = get_asset_directory();
    
    load_all_maps_in_directory(p);
}

game_map& game_map_repository::get_map(util::value_ref<std::string> name) const
{
    return *(this->maps.at(name));
}

boost::filesystem::path game_map_repository::get_asset_directory() const
{
    if (boost::filesystem::is_directory("../../assets/maps"))
    {
        return {"../../assets/maps"};
    }
    else
    {
        return boost::filesystem::current_path() / "maps";
    }
}

void game_map_repository::load_all_maps_in_directory(
    util::value_ref<boost::filesystem::path> p)
{
    using boost::filesystem::directory_iterator;

    for (auto const entry : boost::make_iterator_range(directory_iterator{p}, 
                                                       directory_iterator{}))
    {
        auto const p = entry.path();

        if (p.extension() == ".som")
        {
            load_map(p);
        }
    }
}

void game_map_repository::load_map(
    util::value_ref<boost::filesystem::path> p)
{
    auto map_name = p.filename().string();
    
    auto t = this->loader.load_terrain(p.string());

    auto m = std::make_unique<game_map>(map_name, std::move(t));

    this->maps.emplace(std::move(map_name), std::move(m));
}

}
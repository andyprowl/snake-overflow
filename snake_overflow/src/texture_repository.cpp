#include "stdafx.hpp"

#include "snake_overflow/texture_repository.hpp"
#include <cinder/ImageIo.h>

namespace snake_overflow
{

texture_repository::texture_repository()
{
    cinder::app::addAssetDirectory(boost::filesystem::current_path());

    auto const p = get_asset_directory();
    
    load_all_textures_in_directory(p);
}

cinder::gl::Texture texture_repository::get_texture(
    util::value_ref<std::string> name) const
{
    return this->textures.at(name);
}

boost::filesystem::path texture_repository::get_asset_directory() const
{
    if (boost::filesystem::is_directory("../../assets/textures"))
    {
        return {"../../assets/textures"};
    }
    else
    {
        return boost::filesystem::current_path() / "textures";
    }
}

void texture_repository::load_all_textures_in_directory(
    util::value_ref<boost::filesystem::path> p)
{
    using boost::filesystem::directory_iterator;

    for (auto const entry : boost::make_iterator_range(directory_iterator{p}, 
                                                       directory_iterator{}))
    {
        load_texture(entry.path());
    }
}

void texture_repository::load_texture(
    util::value_ref<boost::filesystem::path> p)
{
    auto texture_name = p.stem().filename().string();

    auto asset_name = "textures/" + p.filename().string();

    auto const texture_asset = cinder::app::loadAsset(asset_name);

    this->textures[texture_name] = cinder::loadImage(texture_asset);
}

}
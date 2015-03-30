#include "stdafx.hpp"

#include "snake_overflow/texture_repository.hpp"
#include "cinder/ImageIo.h"

namespace snake_overflow
{

texture_repository::texture_repository()
{
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
    return {"../../assets/textures"};
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
    auto texture_name = p.filename().string();

    auto asset_name = "textures/" + p.filename().string();

    auto const texture_asset = cinder::app::loadAsset(asset_name);

    this->textures[texture_name] = cinder::loadImage(texture_asset);
}

}
#pragma once

#include "util/value_ref.hpp"
#include "cinder/gl/Texture.h"
#include "boost/filesystem.hpp"
#include <string>
#include <unordered_map>

namespace snake_overflow
{

class texture_repository
{

public:

    texture_repository();

    cinder::gl::Texture get_texture(util::value_ref<std::string> name) const;

private:

    boost::filesystem::path get_asset_directory() const;

    void load_all_textures_in_directory(
        util::value_ref<boost::filesystem::path> p);

    void load_texture(util::value_ref<boost::filesystem::path> p);

private:

    std::unordered_map<std::string, cinder::gl::Texture> textures;

};

}
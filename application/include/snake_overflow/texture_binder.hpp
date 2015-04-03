#pragma once

#include "util/value_ref.hpp"
#include "cinder/gl/Texture.h"

namespace snake_overflow
{

class texture_repository;

struct texture_binder
{

public:

    texture_binder(cinder::gl::Texture texture);

    texture_binder(texture_repository const& textures, 
                   util::value_ref<std::string> name);

    texture_binder(texture_binder const& rhs) = delete;

    texture_binder(texture_binder&& rhs);

    texture_binder& operator = (texture_binder const& rhs) = delete;

    texture_binder& operator = (texture_binder&& rhs);

    ~texture_binder();

private:

    cinder::gl::Texture texture;

};

}
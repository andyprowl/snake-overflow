#include "stdafx.hpp"

#include "snake_overflow/texture_binder.hpp"
#include "snake_overflow/texture_repository.hpp"

namespace snake_overflow
{    

cinder::gl::Texture try_get_texture(texture_repository const& textures,
                                    util::value_ref<std::string> name)
{
    if (!name.empty())
    {
        try
        {
            return textures.get_texture(name);
        }
        catch (std::exception const&)
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}

texture_binder::texture_binder(cinder::gl::Texture texture)
    : texture{std::move(texture)}
{
    if (this->texture)
    {
        this->texture.enableAndBind();
    }
}

texture_binder::texture_binder(texture_repository const& textures, 
                               util::value_ref<std::string> name)
    : texture_binder{try_get_texture(textures, name)}
{
}

texture_binder::texture_binder(texture_binder&& rhs)
    : texture{std::move(rhs.texture)}
{
    rhs.texture.reset();
}

texture_binder& texture_binder::operator = (texture_binder&& rhs)
{
    this->texture = std::move(rhs.texture);

    rhs.texture.reset();

    return *this;
}

texture_binder::~texture_binder()
{
    if (this->texture)
    {
        this->texture.unbind();
    }
}


}
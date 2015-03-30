#include "stdafx.hpp"

#include "snake_overflow/texture_binder.hpp"
#include "snake_overflow/texture_repository.hpp"

namespace snake_overflow
{

texture_binder::texture_binder(texture_repository const& textures, 
                               util::value_ref<std::string> name)
{
    if (!name.empty())
    {
        this->texture = textures.get_texture(name);
    
        this->texture.enableAndBind();
    }
}

texture_binder::~texture_binder()
{
    if (this->texture)
    {
        this->texture.unbind();
    }
}

}
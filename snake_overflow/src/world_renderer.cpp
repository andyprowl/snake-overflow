#include "stdafx.hpp"

#include "snake_overflow/texture_repository.hpp"
#include "snake_overflow/world_renderer.hpp"

namespace snake_overflow
{

world_renderer::world_renderer(float const block_size, 
                               texture_repository const& textures)
{
    create_snake_renderer(block_size, textures);

    create_item_renderer(block_size, textures);

    create_terrain_renderer(block_size, textures);
}

void world_renderer::render(snake const& s, terrain const& t) const
{
    this->snake_drawer->render(s);

    this->item_drawer->render(t);

    this->terrain_drawer->render(t);
}

void world_renderer::create_snake_renderer(float const block_size,
                                           texture_repository const& textures)
{
    float snake_width = block_size / 2;

    float snake_height = snake_width;

    auto const skin = textures.get_texture("snake6.jpg");

    this->snake_drawer = std::make_unique<snake_renderer>(snake_width, 
                                                          snake_height, 
                                                          block_size,
                                                          skin);
}

void world_renderer::create_item_renderer(float const block_size,
                                          texture_repository const& textures)
{
    this->item_drawer = std::make_unique<item_renderer>(block_size, 
                                                        textures);
}

void world_renderer::create_terrain_renderer(float const block_size,
                                             texture_repository const& textures)
{
    this->terrain_drawer = std::make_unique<terrain_renderer>(block_size, 
                                                              textures);
}

}
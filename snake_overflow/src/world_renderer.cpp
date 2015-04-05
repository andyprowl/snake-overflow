#include "stdafx.hpp"

#include "snake_overflow/texture_repository.hpp"
#include "snake_overflow/world_renderer.hpp"

namespace snake_overflow
{

world_renderer::world_renderer(terrain const& t,
                               snake const& s,
                               float const block_size, 
                               texture_repository const& textures)
{
    create_snake_renderer(s, block_size, textures);

    create_item_renderer(t, block_size, textures);

    create_terrain_renderer(t, block_size, textures);
}

void world_renderer::render() const
{
    this->snake_drawer->render();

    this->item_drawer->render();

    this->terrain_drawer->render();
}

void world_renderer::create_snake_renderer(snake const& s,
                                           float const block_size,
                                           texture_repository const& textures)
{
    float snake_width = block_size / 2;

    float snake_height = snake_width;

    auto const skin = textures.get_texture("snake6.jpg");

    this->snake_drawer = std::make_unique<snake_renderer>(s,
                                                          snake_width, 
                                                          snake_height, 
                                                          block_size,
                                                          skin);
}

void world_renderer::create_item_renderer(terrain const& t,
                                          float const block_size,
                                          texture_repository const& textures)
{
    this->item_drawer = std::make_unique<item_renderer>(t,
                                                        block_size, 
                                                        textures);
}

void world_renderer::create_terrain_renderer(terrain const& t,
                                             float const block_size,
                                             texture_repository const& textures)
{
    this->terrain_drawer = std::make_unique<terrain_renderer>(t,
                                                              block_size, 
                                                              textures);
}

}
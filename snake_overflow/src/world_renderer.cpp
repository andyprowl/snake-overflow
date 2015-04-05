#include "stdafx.hpp"

#include "snake_overflow/game.hpp"
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

void world_renderer::set_current_game(game const& g)
{
    this->snake_drawer->set_current_snake(g.get_snake());

    this->item_drawer->set_current_terrain(g.get_terrain());

    this->terrain_drawer->set_current_map(g.get_map());
}

void world_renderer::render() const
{
    this->snake_drawer->render();

    this->item_drawer->render();

    this->terrain_drawer->render();
}

void world_renderer::create_snake_renderer(float const block_size,
                                           texture_repository const& textures)
{
    float snake_width = block_size / 2;

    float snake_height = snake_width;

    this->snake_drawer = std::make_unique<snake_renderer>(snake_width, 
                                                          snake_height, 
                                                          block_size,
                                                          textures);
}

void world_renderer::create_item_renderer(float const block_size,
                                          texture_repository const& textures)
{
    this->item_drawer = std::make_unique<item_renderer>(block_size, textures);
}

void world_renderer::create_terrain_renderer(float const block_size,
                                             texture_repository const& textures)
{
    this->terrain_drawer = std::make_unique<terrain_renderer>(block_size, 
                                                              textures);
}

}
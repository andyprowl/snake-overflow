#pragma once

#include "snake_overflow/item_renderer.hpp"
#include "snake_overflow/snake_renderer.hpp"
#include "snake_overflow/terrain_renderer.hpp"

namespace snake_overflow
{

class snake;
class terrain;
class texture_repository;

class world_renderer
{

public:

    world_renderer(float block_size, 
                   texture_repository const& textures);

    void render(snake const& s, terrain const& t) const;

private:

    void create_snake_renderer(float block_size,
                               texture_repository const& textures);

    void create_item_renderer(float const block_size,
                              texture_repository const& textures);

    void create_terrain_renderer(float const block_size,
                                 texture_repository const& textures);

private:

    std::unique_ptr<snake_renderer> snake_drawer;

    std::unique_ptr<item_renderer> item_drawer;

    std::unique_ptr<terrain_renderer> terrain_drawer;
    
};

}
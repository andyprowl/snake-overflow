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

    world_renderer(terrain const& t,
                   snake const& s,
                   float block_size, 
                   texture_repository const& textures);

    void render() const;

private:

    void create_snake_renderer(snake const& s,
                               float block_size,
                               texture_repository const& textures);

    void create_item_renderer(terrain const& t,
                              float const block_size,
                              texture_repository const& textures);

    void create_terrain_renderer(terrain const& t,
                                 float const block_size,
                                 texture_repository const& textures);

private:

    std::unique_ptr<snake_renderer> snake_drawer;

    std::unique_ptr<item_renderer> item_drawer;

    std::unique_ptr<terrain_renderer> terrain_drawer;
    
};

}
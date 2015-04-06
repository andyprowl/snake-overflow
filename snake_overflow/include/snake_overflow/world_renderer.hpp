#pragma once

#include "snake_overflow/item_renderer.hpp"
#include "snake_overflow/snake_renderer.hpp"
#include "snake_overflow/terrain_renderer.hpp"

namespace snake_overflow
{

class game;
class game_map;
class game_map_block_cache;
class texture_repository;

class world_renderer
{

public:

    world_renderer(float block_size, 
                   texture_repository const& textures,
                   game_map_block_cache const& terrain_block_cache);

    void set_current_game(game const& g);

    void render() const;

private:

    void create_snake_renderer(float block_size,
                               texture_repository const& textures);

    void create_item_renderer(float const block_size,
                              texture_repository const& textures);

    void create_terrain_renderer(
        float const block_size,
        texture_repository const& textures,
        game_map_block_cache const& terrain_block_cache);

private:

    game const* current_game = nullptr;

    std::unique_ptr<snake_renderer> snake_drawer;

    std::unique_ptr<item_renderer> item_drawer;

    std::unique_ptr<terrain_renderer> terrain_drawer;
    
};

}
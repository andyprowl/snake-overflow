#pragma once

#include "snake_overflow/block.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{

struct block;

class game_map;
class game_map_block_cache;
class terrain;
class texture_repository;

class terrain_renderer
{

public:

    terrain_renderer(float block_size, 
                     texture_repository const& textures,
                     game_map_block_cache const& block_cache);

    void set_current_map(game_map const& m);

    void render() const;

private:

    void render_block(util::value_ref<block> b) const;

private:

    game_map const* current_map = nullptr;

    float block_size;

    texture_repository const& textures;

    std::vector<block> blocks_to_render;

    game_map_block_cache const& block_cache;

};

}
#pragma once

#include "snake_overflow/block.hpp"
#include "snake_overflow/game_map_block_cache.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{

struct block;

class terrain;
class texture_repository;

class terrain_renderer
{

public:

    terrain_renderer(float block_size, 
                     texture_repository const& textures);

    void set_current_map(game_map const& m);

    void render() const;

private:

    void render_block(util::value_ref<block> b) const;

private:

    game_map const* current_map = nullptr;

    float block_size;

    texture_repository const& textures;

    std::vector<block> blocks_to_render;

    game_map_block_cache block_cache;

};

}
#pragma once

#include "snake_overflow/block.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{

struct block;

class terrain;
class texture_repository;

class terrain_renderer
{

public:

    terrain_renderer(terrain const& t,
                     float block_size, 
                     texture_repository const& textures);

    void render() const;

private:

    std::vector<block> get_visible_blocks(terrain const& t) const;

    bool is_block_occluded(util::value_ref<block> b, terrain const& t) const;

    void sort_blocks_for_rendering(std::vector<block>& blocks) const;

    void render_block(util::value_ref<block> b) const;

private:

    float block_size;

    texture_repository const& textures;

    std::vector<block> blocks_to_render;

};

}
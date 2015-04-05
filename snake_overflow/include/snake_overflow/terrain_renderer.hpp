#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

struct block;

class terrain;
class texture_repository;

class terrain_renderer
{

public:

    terrain_renderer(float block_size, texture_repository const& textures);

    void render(util::value_ref<terrain> t) const;

private:

    void render_block_if_visible(util::value_ref<block> b) const;

    void render_block(util::value_ref<block> b) const;

private:

    float block_size;

    texture_repository const& textures;

};

}
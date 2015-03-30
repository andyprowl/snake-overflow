#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

struct block;

class territory;
class texture_repository;

class territory_renderer
{

public:

    territory_renderer(float block_size, texture_repository const& textures);

    void render(util::value_ref<territory> t) const;

private:

    void render_block(util::value_ref<block> b) const;

private:

    float block_size;

    texture_repository const& textures;

};

}
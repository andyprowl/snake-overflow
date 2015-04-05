#include "stdafx.hpp"

#include "snake_overflow/alpha_blending_enabler.hpp"
#include "snake_overflow/block.hpp"
#include "snake_overflow/color_conversion.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_renderer.hpp"
#include "snake_overflow/texture_binder.hpp"
#include "snake_overflow/texture_repository.hpp"
#include <algorithm>
#include <iterator>

namespace snake_overflow
{

terrain_renderer::terrain_renderer(float const block_size,
                                   texture_repository const& textures)
    : block_size{block_size}
    , textures{textures}
{
}

void terrain_renderer::set_current_map(game_map const& m)
{
    this->blocks_to_render = this->block_cache.get_map_blocks(m);
}

void terrain_renderer::render() const
{
    for (auto const& b : this->blocks_to_render)
    {
        auto const is_translucent = is_block_translucent(b);

        auto const blending_activator = alpha_blending_enabler{is_translucent};

        render_block(b);
    }
}

void terrain_renderer::render_block(util::value_ref<block> b) const
{
    auto const block_size = this->block_size;

    auto const block_cube = cinder::Vec3f{block_size, block_size, block_size};

    auto const block_origin = vec3f_from_point(b.origin) * block_size;

    auto const color = color_from_rgba_color(b.color);

    cinder::gl::color(color); 

    auto const binder = texture_binder{this->textures, b.texture};

    cinder::gl::drawCube(block_origin, block_cube);
}

}
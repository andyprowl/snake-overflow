#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/color_conversion.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_renderer.hpp"
#include "snake_overflow/texture_binder.hpp"
#include "snake_overflow/texture_repository.hpp"

namespace snake_overflow
{

terrain_renderer::terrain_renderer(float const block_size,
                                   texture_repository const& textures)
    : block_size{block_size}
    , textures{textures}
{
}

void terrain_renderer::render(util::value_ref<terrain> t) const
{
    t.for_each_block([this] (util::value_ref<block> b)
    {
        render_block_if_visible(b);
    });
}

void terrain_renderer::render_block_if_visible(util::value_ref<block> b) const
{
    if (!is_block_visible(b)) { return; }
    
    if (b.color.alpha < 255)
    {
        cinder::gl::enableAlphaBlending();
    }

    render_block(b);

    if (b.color.alpha < 255)
    {
        cinder::gl::disableAlphaBlending();
    }
}

void terrain_renderer::render_block(util::value_ref<block> b) const
{
    auto const block_cube = cinder::Vec3f{this->block_size, 
                                          this->block_size, 
                                          this->block_size};

    auto const block_origin = vec3f_from_point(b.origin) * block_size;

    auto const color = color_from_rgba_color(b.color);

    cinder::gl::color(color); 

    auto const binder = texture_binder{this->textures, b.texture};

    cinder::gl::drawCube(block_origin, block_cube);
}

}
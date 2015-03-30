#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/territory.hpp"
#include "snake_overflow/territory_renderer.hpp"
#include "snake_overflow/texture_repository.hpp"

namespace snake_overflow
{

territory_renderer::territory_renderer(float const block_size,
                                       texture_repository const& textures)
    : block_size{block_size}
    , textures{textures}
{
}

void territory_renderer::render(util::value_ref<territory> t) const
{
    auto const& blocks = t.get_blocks();

    for (auto const& b : blocks)
    {
        render_block(b);
    }
}

void territory_renderer::render_block(util::value_ref<block> b) const
{
    auto const block_cube = cinder::Vec3f{this->block_size, 
                                          this->block_size, 
                                          this->block_size};

    auto const block_origin = vec3f_from_point(b.origin) * block_size;

    cinder::gl::color(cinder::Color{1.0, 1.0, 1.0}); 

    auto tex = this->textures.get_texture(b.texture);
    
    tex.enableAndBind();

    cinder::gl::drawCube(block_origin, block_cube);

    tex.unbind();
}

}
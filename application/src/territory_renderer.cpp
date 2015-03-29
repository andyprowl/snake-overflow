#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/territory.hpp"
#include "snake_overflow/territory_renderer.hpp"

namespace snake_overflow
{

territory_renderer::territory_renderer(float const block_size)
    : block_size{block_size}
{
}

void territory_renderer::render(territory& t) const
{
    auto const blocks = t.get_blocks();

    for (auto const& b : blocks)
    {
        render_block(b);
    }
}

void territory_renderer::render_block(util::value_ref<block> b) const
{
    auto origin = b.get_origin();

    auto const block_cube = cinder::Vec3f{this->block_size, 
                                          this->block_size, 
                                          this->block_size};

    auto const block_origin = vector_from_point(origin) * block_size;

    cinder::gl::color(cinder::Color{1.0, 1.0, 1.0});

    cinder::gl::drawCube(block_origin, block_cube);
}

}
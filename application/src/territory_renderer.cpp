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

void territory_renderer::render(util::value_ref<territory> t) const
{
    auto const blocks = t.get_blocks();

    for (auto const& b : blocks)
    {
        render_block(b);
    }
}

void territory_renderer::render_block(util::value_ref<block> b) const
{
    auto const origin = b.get_origin();

    auto const block_cube = cinder::Vec3f{this->block_size, 
                                          this->block_size, 
                                          this->block_size};

    auto const block_origin = vec3f_from_point(origin) * block_size;

    cinder::gl::color(cinder::Color{std::fabs(block_origin.x) / 100.f, 
                                    std::fabs(block_origin.y) / 100.f, 
                                    std::fabs(block_origin.z) / 100.f});

    cinder::gl::drawCube(block_origin, block_cube);
}

}
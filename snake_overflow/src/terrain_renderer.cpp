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

terrain_renderer::terrain_renderer(terrain const& t,
                                   float const block_size,
                                   texture_repository const& textures)
    : block_size{block_size}
    , textures{textures}
{
    this->blocks_to_render = get_visible_blocks(t);

    sort_blocks_for_rendering(this->blocks_to_render);
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

std::vector<block> terrain_renderer::get_visible_blocks(terrain const& t) const
{
    auto blocks = t.get_all_blocks();

    auto it = std::remove_if(std::begin(blocks),
                             std::end(blocks),
                             [this, &t] (util::value_ref<block> b)
    {
        return !is_block_visible(b, t);
    });

    blocks.erase(it, std::cend(blocks));

    return blocks;
}

void terrain_renderer::sort_blocks_for_rendering(
    std::vector<block>& blocks) const
{
    std::stable_sort(std::begin(blocks), 
                     std::end(blocks),
                     [] (util::value_ref<block> lhs, 
                         util::value_ref<block> rhs)
    {
        if (lhs.color.alpha == rhs.color.alpha)
        {
            return (lhs.origin < rhs.origin);
        }
        else
        {
            return (lhs.color.alpha > rhs.color.alpha);
        }
    });
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
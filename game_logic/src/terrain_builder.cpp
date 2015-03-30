#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/point.hpp"
#include "util/sequence.hpp"

namespace snake_overflow
{

using util::sequence;

terrain_builder::terrain_builder(terrain& build_site)
    : build_site{build_site}
{
}

void terrain_builder::add_cuboid(util::value_ref<point> origin, 
                                 util::value_ref<point> sizes, 
                                 util::value_ref<std::string> texture,
                                 util::value_ref<rgba_color> color,
                                 bool const solid,
                                 bool const full) const
{
    for (auto const x : sequence(0, sizes.x))
    {
        for (auto const y : sequence(0, sizes.y))
        {
            for (auto const z : sequence(0, sizes.z))
            {
                if (full || is_surface_block(x, y, z, sizes))
                {
                    this->build_site.add_block({origin + point{x, y, z}, 
                                                texture,
                                                color,
                                                solid});
                }
            }
        }
    }
}

void terrain_builder::add_cube(util::value_ref<point> origin, 
                               int const side_length,
                               util::value_ref<std::string> texture,
                               util::value_ref<rgba_color> color,
                               bool const solid,
                               bool const full) const
{
    add_cuboid(origin, 
               {side_length, side_length, side_length},
               texture,
               color,
               solid,
               full);
}

void terrain_builder::add_centered_cuboid(util::value_ref<point> center, 
                                          util::value_ref<point> sizes,
                                          util::value_ref<std::string> texture,
                                          util::value_ref<rgba_color> color,
                                          bool const solid,
                                          bool const full) const
{
    auto const half_sizes = point{sizes.x / 2, sizes.y / 2, sizes.z / 2};
    
    auto const origin = center - half_sizes;

    add_cuboid(origin, sizes, texture, color, solid, full);
}

void terrain_builder::add_centered_cube(util::value_ref<point> center, 
                                        int const side_length,
                                        util::value_ref<std::string> texture,
                                        util::value_ref<rgba_color> color,
                                        bool const solid,
                                        bool const full) const
{
    add_centered_cuboid(center, 
                        {side_length, side_length, side_length}, 
                        texture, 
                        color, 
                        solid,
                        full);
}

void terrain_builder::remove_cuboid(util::value_ref<point> origin, 
                                    util::value_ref<point> sizes) const
{
    for (auto const x : sequence(0, sizes.x))
    {
        for (auto const y : sequence(0, sizes.y))
        {
            for (auto const z : sequence(0, sizes.z))
            {
                this->build_site.remove_block(origin + point{x, y, z});
            }
        }
    }
}

bool terrain_builder::is_surface_block(int const x, 
                                       int const y, 
                                       int const z, 
                                       util::value_ref<point> sizes) const
{
    return ((x == 0) || (x == sizes.x - 1) ||
            (y == 0) || (y == sizes.y - 1) ||
            (z == 0) || (z == sizes.z - 1));
}

}
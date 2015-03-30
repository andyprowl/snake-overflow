#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/cube_builder.hpp"
#include "snake_overflow/territory.hpp"
#include "snake_overflow/point.hpp"
#include "util/sequence.hpp"

namespace snake_overflow
{

using util::sequence;

cube_builder::cube_builder(territory& build_site)
    : build_site{build_site}
{
}

bool is_surface_block(int const x, 
                      int const y, 
                      int const z, 
                      int const side_length)
{
    return ((x == 0) || (x == side_length - 1) ||
            (y == 0) || (y == side_length - 1) ||
            (z == 0) || (z == side_length - 1));
}

void cube_builder::add_cube(util::value_ref<point> origin, 
                            int const side_length) const
{
    for (auto const x : sequence(origin.x, origin.x + side_length))
    {
        for (auto const y : sequence(origin.y, origin.y + side_length))
        {
            for (auto const z : sequence(origin.z, origin.z + side_length))
            {
                if (is_surface_block(x, y, z, side_length))
                {
                    this->build_site.add_block(point{x, y, z});
                }
            }
        }
    }
}

void cube_builder::add_centered_cube(util::value_ref<point> center, 
                                     int const side_length) const
{
    auto const half_length = side_length / 2;

    for (auto const x : sequence(center.x, center.x + side_length))
    {
        for (auto const y : sequence(center.y, center.y + side_length))
        {
            for (auto const z : sequence(center.z, center.z + side_length))
            {
                if (is_surface_block(x, y, z, side_length))
                {
                    this->build_site.add_block(
                        point{x - half_length, 
                              y - half_length, 
                              z - half_length});
                }
            }
        }
    }
}

}
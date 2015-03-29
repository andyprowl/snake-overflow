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

void cube_builder::add_cube(util::value_ref<point> origin, 
                            int const side_length) const
{
    for (auto const x : sequence(origin.x, origin.x + side_length))
    {
        for (auto const y : sequence(origin.y, origin.y + side_length))
        {
            for (auto const z : sequence(origin.z, origin.z + side_length))
            {
                this->build_site.add_block(point{x, y, z});
            }
        }
    }
}

}
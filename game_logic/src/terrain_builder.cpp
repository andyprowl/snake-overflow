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

template<typename F>
void for_each_point_in_box(util::value_ref<point> lower_bound,
                           util::value_ref<point> upper_bound,
                           F f)
{
    for (auto const x : sequence(lower_bound.x, upper_bound.x))
    {
        for (auto const y : sequence(lower_bound.x, upper_bound.y))
        {
            for (auto const z : sequence(lower_bound.x, upper_bound.z))
            {
                f({x, y, z});
            }
        }
    }
}

void terrain_builder::add_box(util::value_ref<point> origin, 
                              util::value_ref<point> sizes, 
                              util::value_ref<std::string> texture,
                              util::value_ref<rgba_color> color,
                              bool const solid) const
{
    for_each_point_in_box(
        point::zero(), 
        sizes, 
        [this, &origin, &sizes, &color, &texture, &solid] 
        (util::value_ref<point> p)
    {
        if (is_surface_block(p.x, p.y, p.z, sizes))
        {
            this->build_site.add_block({p + origin, texture, color, solid});
        }
        else
        {
            this->build_site.add_block({p + origin, "", {0, 0, 0, 0}, solid});
        }
    });
}

void terrain_builder::add_cube(util::value_ref<point> origin, 
                               int const side_length,
                               util::value_ref<std::string> texture,
                               util::value_ref<rgba_color> color,
                               bool const solid) const
{
    auto const sizes = point{side_length, side_length, side_length};

    add_box(origin, sizes, texture, color, solid);
}

void terrain_builder::add_centered_box(util::value_ref<point> center, 
                                       util::value_ref<point> sizes,
                                       util::value_ref<std::string> texture,
                                       util::value_ref<rgba_color> color,
                                       bool const solid) const
{
    auto const half_sizes = point{sizes.x / 2, sizes.y / 2, sizes.z / 2};
    
    auto const origin = center - half_sizes;

    add_box(origin, sizes, texture, color, solid);
}

void terrain_builder::add_centered_cube(util::value_ref<point> center, 
                                        int const side_length,
                                        util::value_ref<std::string> texture,
                                        util::value_ref<rgba_color> color,
                                        bool const solid) const
{
    auto const sizes = point{side_length, side_length, side_length};

    add_centered_box(center, sizes, texture, color, solid);
}

void terrain_builder::remove_box(util::value_ref<point> origin, 
                                 util::value_ref<point> sizes) const
{
    for_each_point_in_box(point::zero(), 
                          sizes, 
                          [this, &origin] (util::value_ref<point> p)
    {
        this->build_site.remove_block(origin + p);
    });
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
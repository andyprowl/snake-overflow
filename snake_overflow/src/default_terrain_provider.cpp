#include "stdafx.hpp"

#include "snake_overflow/default_terrain_provider.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"

namespace snake_overflow
{

std::unique_ptr<terrain> default_terrain_provider::create_terrain(
    util::value_ref<std::string>)
{
    auto habitat = std::make_unique<terrain>();

    auto builder = terrain_builder{*habitat};

    auto cube_side_length = 20;

    builder.add_centered_cube({0, 0, 0}, 
                              cube_side_length, 
                              "grass4.jpg",
                              {255, 255, 255, 255},
                              true);

    builder.add_box({-cube_side_length / 2, 
                     -cube_side_length / 4, 
                     cube_side_length / 4 + 4}, 
                    {7, 6, 4}, 
                    "lava5.jpg",
                    {255, 255, 255, 255},
                    true);

    builder.add_cube({0, -cube_side_length / 2 - 7, 0}, 
                     7, 
                     "stone3.jpg",
                     {255, 255, 255, 255},
                     true);

    builder.add_cube({0, 0, cube_side_length / 2}, 
                     1, 
                     "stone3.jpg",
                     {255, 255, 255, 255},
                     true);

    auto const pool_sizes = point{7, 9, 3};

    auto const pool_origin = point{cube_side_length / 2,
                                   cube_side_length / 2 - pool_sizes.y,
                                   cube_side_length / 4};

    builder.add_box(pool_origin,
                    pool_sizes,
                    "lava3.jpg",
                    {255, 255, 255, 255},
                    true);

    builder.remove_box(pool_origin + point{1, 1, 1},
                       pool_sizes - point{2, 2, 1});

    builder.add_box(pool_origin + point{1, 1, 1}, 
                    pool_sizes - point{2, 2, 1},
                    "water4.jpg",
                    {255, 255, 255, 100},
                    false,
                    false);

    habitat->sort_for_rendering();

    return std::move(habitat);
}

}
#pragma once

#include "snake_overflow/point.hpp"
#include "snake_overflow/rgba_color.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{

class terrain;

class terrain_builder
{

public:

    terrain_builder(terrain& build_site);

    void add_box(util::value_ref<point> origin, 
                 util::value_ref<point> sizes, 
                 util::value_ref<std::string> texture,
                 util::value_ref<rgba_color> color,
                 bool solid,
                 bool invisible_inside = true) const;

    void add_cube(util::value_ref<point> origin, 
                  int side_length, 
                  util::value_ref<std::string> texture,
                  util::value_ref<rgba_color> color,
                  bool solid,
                  bool invisible_inside = true) const;

    void add_centered_box(util::value_ref<point> center, 
                          util::value_ref<point> sizes, 
                          util::value_ref<std::string> texture,
                          util::value_ref<rgba_color> color,
                          bool solid,
                          bool invisible_inside = true) const;

    void add_centered_cube(util::value_ref<point> center, 
                           int const side_length,
                           util::value_ref<std::string> texture,
                           util::value_ref<rgba_color> color,
                           bool solid,
                           bool invisible_inside = true) const;

    void remove_box(util::value_ref<point> origin, 
                    util::value_ref<point> sizes) const;

private:

    bool is_surface_block(int x, 
                          int y, 
                          int z, 
                          util::value_ref<point> sizes) const;

private:

    terrain& build_site;

};

}
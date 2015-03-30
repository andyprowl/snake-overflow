#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

struct point;
struct rgba_color;

class terrain;

class terrain_builder
{

public:

    terrain_builder(terrain& build_site);

    void add_cuboid(util::value_ref<point> origin, 
                    util::value_ref<point> sizes, 
                    util::value_ref<std::string> texture,
                    util::value_ref<rgba_color> color,
                    bool solid) const;

    void add_cube(util::value_ref<point> origin, 
                  int side_length, 
                  util::value_ref<std::string> texture,
                  util::value_ref<rgba_color> color,
                  bool solid) const;

    void add_centered_cuboid(util::value_ref<point> center, 
                             util::value_ref<point> sizes, 
                             util::value_ref<std::string> texture,
                             util::value_ref<rgba_color> color,
                             bool solid) const;

    void add_centered_cube(util::value_ref<point> center, 
                           int const side_length,
                           util::value_ref<std::string> texture,
                           util::value_ref<rgba_color> color,
                           bool solid) const;

private:

    terrain& build_site;

};

}
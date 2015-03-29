#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

struct point;

class territory;

class cube_builder
{

public:

    cube_builder(territory& build_site);

    void add_cube(util::value_ref<point> origin, int side_length) const;
    
private:

    territory& build_site;

};

}
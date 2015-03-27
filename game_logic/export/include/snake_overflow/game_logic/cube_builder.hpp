#pragma once

#include "util/value_ref.hpp"

namespace math
{

struct point3d;

}

namespace snake_overflow { namespace game_logic
{

class territory;

class cube_builder
{

public:

    cube_builder(territory& build_site);

    void add_cube(util::value_ref<math::point3d> origin, 
                  int side_length) const;
    
private:

    territory& build_site;

};

} }
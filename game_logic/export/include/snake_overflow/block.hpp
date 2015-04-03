#pragma once

#include "snake_overflow/point.hpp"
#include "snake_overflow/rgba_color.hpp"
#include "util/value_ref.hpp"
#include <string>
#include <vector>

namespace snake_overflow
{

class item;
    
struct block
{

public:

    block(util::value_ref<point> origin, 
          std::string texture, 
          util::value_ref<rgba_color> c,
          bool is_solid);

public:

    point origin;

    std::string texture;

    rgba_color color;

    bool is_solid;

    std::vector<item*> items;
    
};

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs);

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs);

bool is_block_visible(util::value_ref<block> b);

}
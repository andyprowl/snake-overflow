#pragma once

#include "snake_overflow/rgba_color.hpp"
#include "util/value_ref.hpp"
#include <string>

namespace snake_overflow
{
    
struct block_type
{

public:

    block_type(std::string texture, 
               util::value_ref<rgba_color> c,
               bool is_solid);

public:

    std::string texture;

    rgba_color color;

    bool is_solid;
    
};

}
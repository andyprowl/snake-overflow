#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

struct rgba_color
{

public:

    rgba_color(unsigned char r, 
               unsigned char g, 
               unsigned char b, 
               unsigned char alpha);

public:

    unsigned char r;

    unsigned char g;

    unsigned char b;

    unsigned char alpha;

};

bool operator == (util::value_ref<rgba_color> lhs, 
                  util::value_ref<rgba_color> rhs);

bool operator != (util::value_ref<rgba_color> lhs, 
                  util::value_ref<rgba_color> rhs);

}
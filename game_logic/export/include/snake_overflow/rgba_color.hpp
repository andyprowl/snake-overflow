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

    static rgba_color black();

    static rgba_color red();

    static rgba_color green();

    static rgba_color blue();

    static rgba_color yellow();

    static rgba_color purple();

    static rgba_color cyan();

    static rgba_color white();

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
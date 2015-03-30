#pragma once

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

}
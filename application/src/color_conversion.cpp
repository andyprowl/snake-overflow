#include "stdafx.hpp"

#include "snake_overflow/color_conversion.hpp"
#include "snake_overflow/rgba_color.hpp"

namespace snake_overflow
{

cinder::ColorA color_from_rgba_color(util::value_ref<rgba_color> c)
{
    return {c.r / 255.f, c.g / 255.f, c.b / 255.f, c.alpha / 255.f};
}

}
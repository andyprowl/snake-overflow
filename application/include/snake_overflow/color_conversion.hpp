#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

struct rgba_color;

cinder::ColorA color_from_rgba_color(util::value_ref<rgba_color> c);

}
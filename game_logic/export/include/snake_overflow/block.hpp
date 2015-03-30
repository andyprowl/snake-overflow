#pragma once

#include "snake_overflow/point.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{
    
struct block
{

public:

    block(util::value_ref<point> origin, std::string texture);

public:

    point origin;

    std::string texture;
    
};

bool operator == (util::value_ref<block> lhs, util::value_ref<block> rhs);

bool operator != (util::value_ref<block> lhs, util::value_ref<block> rhs);

}
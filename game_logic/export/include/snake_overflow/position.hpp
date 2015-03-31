#pragma once

#include "snake_overflow/block_face.hpp"
#include "snake_overflow/point.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{

struct position
{

public:

    position(util::value_ref<point> location, block_face face);

public:

    point location;

    block_face face;

};

bool operator == (util::value_ref<position> lhs, 
                  util::value_ref<position> rhs);

bool operator != (util::value_ref<position> lhs, 
                  util::value_ref<position> rhs);

}

namespace std
{

template<>
struct hash<snake_overflow::position>
{

public:

    std::size_t operator () (util::value_ref<snake_overflow::position> p)
    {
        return (std::hash<snake_overflow::point>{}(p.location) ^
                std::hash<std::size_t>{}(static_cast<std::size_t>(p.face)));
    }

};

}
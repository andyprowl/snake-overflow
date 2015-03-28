#pragma once

#include "util/value_ref.hpp"
#include <functional>

namespace snake_overflow { namespace game_logic
{

struct point3d;

enum class cartesian_axis
{
    x,
    y,
    z
};

enum class orientation
{
    positive,
    negative
};

struct direction
{

public:

    direction(cartesian_axis axis, orientation way);

    static direction positive_x();

    static direction negative_x();

    static direction positive_y();

    static direction negative_y();

    static direction positive_z();

    static direction negative_z();

public:

    cartesian_axis axis;

    orientation way;

};

bool operator == (util::value_ref<direction> lhs, 
                  util::value_ref<direction> rhs);

bool operator != (util::value_ref<direction> lhs, 
                  util::value_ref<direction> rhs);

point3d get_direction_vector(util::value_ref<direction> dir);

direction get_opposite_direction(direction d);

} }

namespace std
{

template<>
struct hash<snake_overflow::game_logic::direction>
{

public:

    std::size_t operator () (snake_overflow::game_logic::direction const d)
    {
        return (std::hash<std::size_t>{}(static_cast<std::size_t>(d.axis)) ^
                std::hash<std::size_t>{}(static_cast<std::size_t>(d.way)));
    }

};

}
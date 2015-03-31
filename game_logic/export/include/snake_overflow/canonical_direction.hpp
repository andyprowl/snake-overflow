#pragma once

#include "util/value_ref.hpp"
#include <functional>
#include <vector>

namespace snake_overflow
{

struct point;

enum class canonical_axis
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

class bad_direction_vector_exception : public virtual std::exception
{
};

struct canonical_direction
{

public:

    canonical_direction(canonical_axis axis, orientation way);

    static canonical_direction positive_x();

    static canonical_direction negative_x();

    static canonical_direction positive_y();

    static canonical_direction negative_y();

    static canonical_direction positive_z();

    static canonical_direction negative_z();

public:

    canonical_axis axis;

    orientation way;

};

bool operator == (util::value_ref<canonical_direction> lhs, 
                  util::value_ref<canonical_direction> rhs);

bool operator != (util::value_ref<canonical_direction> lhs, 
                  util::value_ref<canonical_direction> rhs);

point get_direction_vector(util::value_ref<canonical_direction> dir);

canonical_direction get_direction_from_vector(util::value_ref<point> v);

canonical_direction get_opposite_direction(
    util::value_ref<canonical_direction> dir);

std::vector<canonical_direction> get_all_canonical_directions();

}

namespace std
{

template<>
struct hash<snake_overflow::canonical_direction>
{

public:

    std::size_t operator () (snake_overflow::canonical_direction const d)
    {
        return (std::hash<std::size_t>{}(static_cast<std::size_t>(d.axis)) ^
                std::hash<std::size_t>{}(static_cast<std::size_t>(d.way)));
    }

};

}
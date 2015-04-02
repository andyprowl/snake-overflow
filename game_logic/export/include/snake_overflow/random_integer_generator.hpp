#pragma once

#include "util/value_ref.hpp"
#include <random>
#include <vector>

namespace snake_overflow
{

class random_integer_generator
{

public:

    int generate(int minimum, int maximum) const;

    int generate_in_weighed_range(
        util::value_ref<std::vector<int>> weights) const;

private:

    std::random_device device;
    
    mutable std::mt19937 random_generator{device()};

};

}
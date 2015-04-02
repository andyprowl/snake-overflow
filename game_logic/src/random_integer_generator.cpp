#include "stdafx.hpp"

#include "snake_overflow/random_integer_generator.hpp"

namespace snake_overflow
{

int random_integer_generator::generate(int minimum, int maximum) const
{
    auto dist = std::uniform_int_distribution<>{minimum, maximum};

    return dist(this->random_generator);
}

int random_integer_generator::generate_in_weighed_range(
    util::value_ref<std::vector<int>> weights) const
{
    auto i = std::size_t{0};
    auto dist = std::discrete_distribution<>(weights.size(),
                                             0.0,
                                             1.0,
                                             [&weights, &i] (double const)
    {
        auto const w = weights[i];
        ++i;
        return w;
     });

    return dist(this->random_generator);
}

}
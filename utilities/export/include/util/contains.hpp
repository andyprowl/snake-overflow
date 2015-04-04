#pragma once

#include "util/value_ref.hpp"
#include <iterator>

namespace util
{

template<typename C, typename T>
bool contains(value_ref<C> container, value_ref<T> element)
{
    auto const it = std::find(std::cbegin(container), 
                              std::cend(container), 
                              element);

    return (it != std::cend(container));
}

}
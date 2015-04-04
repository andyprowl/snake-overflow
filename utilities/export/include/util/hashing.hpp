#pragma once

#include <utility>
#include <functional>

namespace std
{
 
template<typename T, typename U>
struct hash<std::pair<T, U>>
{

public:
    
    std::size_t operator () (std::pair<T, U> const& p) const
    {
        return std::hash<T>{}(p.first) ^ std::hash<U>{}(p.second);
    }

};

}
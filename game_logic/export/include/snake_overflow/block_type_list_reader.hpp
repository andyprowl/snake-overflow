#pragma once

#include "snake_overflow/block_type.hpp"
#include <istream>
#include <unordered_map>

namespace snake_overflow
{

class block_type_list_reader
{

public:

    std::unordered_map<std::string, block_type> from_stream(std::istream& is);

};

}
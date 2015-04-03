#include "stdafx.hpp"

#include "snake_overflow/block_type_list_reader.hpp"

namespace snake_overflow
{

std::unordered_map<std::string, block_type> 
    block_type_list_reader::from_stream(std::istream&)
{
    return {};
}

}
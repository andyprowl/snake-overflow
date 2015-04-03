#pragma once

#include "snake_overflow/serialization/block_type.hpp"
#include <istream>
#include <stdexcept>
#include <unordered_map>

namespace snake_overflow { namespace serialization
{
    
struct block_type;

class bad_block_type_list_exception : public virtual std::exception
{
};

class block_type_list_reader
{

public:

    virtual ~block_type_list_reader() = default;

    virtual std::unordered_map<char, block_type> from_stream(
        std::istream& is) = 0;

};

} }
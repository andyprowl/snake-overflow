#pragma once

#include "util/value_ref.hpp"
#include <istream>
#include <stdexcept>
#include <unordered_map>

namespace snake_overflow
{

struct rgba_color;

}

namespace snake_overflow { namespace serialization
{

struct block_type;

class bad_block_type_list_exception : public virtual std::exception
{
};

class block_type_list_reader
{

public:

    std::unordered_map<char, block_type> from_stream(std::istream& is);

private:

    void read_opening_line(std::istream& is) const;

    void parse_block_type_and_store_it(
        util::value_ref<std::string> s,
        std::unordered_map<char, block_type>& types) const;

    block_type parse_block_type(util::value_ref<std::string> s) const;

    rgba_color parse_color(util::value_ref<std::string> s) const;

};

} }
#pragma once

#include "snake_overflow/serialization/block_type_list_reader.hpp"
#include "util/value_ref.hpp"

namespace snake_overflow
{

struct rgba_color;

}

namespace snake_overflow { namespace serialization
{

class block_type_list_tokenizing_reader : public block_type_list_reader
{

public:

    virtual std::unordered_map<char, block_type> from_stream(
        std::istream& is) override;

private:

    void read_opening_line(std::istream& is) const;

    void parse_block_type_and_store_it(
        util::value_ref<std::string> s,
        std::unordered_map<char, block_type>& types) const;

    block_type parse_block_type(util::value_ref<std::string> s) const;

    rgba_color parse_color(util::value_ref<std::string> s) const;

};

} }
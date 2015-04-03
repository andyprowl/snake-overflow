#include "stdafx.hpp"

#include "snake_overflow/serialization/block_type.hpp"
#include "snake_overflow/serialization/block_type_list_tokenizing_reader.hpp"
#include "snake_overflow/rgba_color.hpp"
#include "util/tokenize.hpp"
#include <boost/algorithm/string.hpp>

namespace snake_overflow { namespace serialization
{

std::unordered_map<char, block_type> 
    block_type_list_tokenizing_reader::from_stream(std::istream& is)
{
    read_opening_line(is);

    auto result = std::unordered_map<char, block_type>{};

    auto line = std::string{};
    while (std::getline(is, line))
    {
        if (line == "END BLOCK TYPES") { return result; }

        if (line.empty()) { continue; }

        if (line[1] != ':') { throw bad_block_type_list_exception{}; }

        parse_block_type_and_store_it(line, result);
    }

    throw bad_block_type_list_exception{};
}

void block_type_list_tokenizing_reader::read_opening_line(
    std::istream& is) const
{
    auto line = std::string{};
    std::getline(is, line);

    if (line != "BEGIN BLOCK TYPES")
    {
        throw bad_block_type_list_exception{};
    }
}

void block_type_list_tokenizing_reader::parse_block_type_and_store_it(
    util::value_ref<std::string> s,
    std::unordered_map<char, block_type>& types) const
{
    auto key = s[0];

    auto b = parse_block_type(s.substr(2));

    types.emplace(key, std::move(b));
}

block_type block_type_list_tokenizing_reader::parse_block_type(
    util::value_ref<std::string> s) const
{
    auto tokens = util::tokenize(s, ";");

    auto texture = tokens[0];

    boost::algorithm::trim(texture);

    auto const color = parse_color(tokens[1]);

    auto material = tokens[2];

    boost::algorithm::trim(material);

    auto const is_solid = (material == "S");

    return {std::move(texture), color, is_solid};
}

rgba_color block_type_list_tokenizing_reader::parse_color(
    util::value_ref<std::string> s) const
{
    auto tokens = util::tokenize(s, ",");

    return {static_cast<unsigned char>(std::stoi(tokens[0])), 
            static_cast<unsigned char>(std::stoi(tokens[1])), 
            static_cast<unsigned char>(std::stoi(tokens[2])), 
            static_cast<unsigned char>(std::stoi(tokens[3]))};
}

} }
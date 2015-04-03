#include "stdafx.hpp"

#include "snake_overflow/serialization/block_type.hpp"
#include "snake_overflow/serialization/block_type_list_reader.hpp"
#include "snake_overflow/rgba_color.hpp"
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>

namespace snake_overflow { namespace serialization
{

std::vector<std::string> make_vector_from_tokens(
    util::value_ref<boost::tokenizer<boost::char_separator<char>>> tokens)
{
    return {std::begin(tokens), std::end(tokens)};
}

std::unordered_map<char, block_type> 
    block_type_list_reader::from_stream(std::istream& is)
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

void block_type_list_reader::parse_block_type_and_store_it(
    util::value_ref<std::string> s,
    std::unordered_map<char, block_type>& types) const
{
    auto key = s[0];

    auto b = parse_block_type(s.substr(2));

    types.emplace(key, std::move(b));
}

void block_type_list_reader::read_opening_line(std::istream& is) const
{
    auto line = std::string{};
    std::getline(is, line);

    if (line != "BEGIN BLOCK TYPES")
    {
        throw bad_block_type_list_exception{};
    }
}

block_type block_type_list_reader::parse_block_type(
    util::value_ref<std::string> s) const
{
    auto const sep = boost::char_separator<char>{";"};
    
    auto tokens = make_vector_from_tokens({s, sep});

    auto texture = tokens[0];

    boost::algorithm::trim(texture);

    auto const color = parse_color(tokens[1]);

    auto material = tokens[2];

    boost::algorithm::trim(material);

    auto const is_solid = (material == "S");

    return {std::move(texture), color, is_solid};
}

rgba_color block_type_list_reader::parse_color(
    util::value_ref<std::string> s) const
{
    auto const sep = boost::char_separator<char>{","};
    
    auto tokens = make_vector_from_tokens({s, sep});

    return {static_cast<unsigned char>(std::stoi(tokens[0])), 
            static_cast<unsigned char>(std::stoi(tokens[1])), 
            static_cast<unsigned char>(std::stoi(tokens[2])), 
            static_cast<unsigned char>(std::stoi(tokens[3]))};
}

} }
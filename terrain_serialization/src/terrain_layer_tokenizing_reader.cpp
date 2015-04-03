#include "stdafx.hpp"

#include "snake_overflow/serialization/terrain_layer_tokenizing_reader.hpp"
#include "snake_overflow/block_face.hpp"
#include "util/sequence.hpp"
#include "util/tokenize.hpp"
#include <boost/algorithm/string.hpp>
#include <functional>

namespace snake_overflow { namespace serialization
{

using transformer = std::function<point(point)>;

struct terrain_layer_tokenizing_reader::layer_origin
{

    layer_origin(int const x, int const y)
        : x{x}
        , y{y}
    {
    }

    int x = 0;

    int y = 0;

};

struct terrain_layer_tokenizing_reader::layer_info
{

    layer_info(block_face const normal,
               int const depth,
               layer_origin const origin)
        : normal{normal}
        , depth{depth}
        , origin{origin}
    {
    }

    block_face normal = block_face::top;

    int depth;

    layer_origin origin;

};

static auto const begin_layer_token = std::string{"BEGIN LAYER"};

static auto const formatted_directions = 
    std::unordered_map<std::string, block_face>{
        {"+x", block_face::right},
        {"-x", block_face::left},
        {"+y", block_face::back},
        {"-y", block_face::front},
        {"+z", block_face::top},
        {"-z", block_face::bottom}};

static auto const transformers = std::unordered_map<block_face, transformer>{
    {block_face::top, [] (point p) { return point{+p.x, +p.y, +p.z}; }},
    {block_face::bottom, [] (point p) { return point{+p.x, -p.y, -p.z}; }},
    {block_face::front, [] (point p) { return point{+p.x, -p.z, p.y}; }},
    {block_face::back, [] (point p) { return point{-p.x, +p.z, +p.y}; }},
    {block_face::left, [] (point p) { return point{-p.y, +p.z, -p.x}; }},
    {block_face::right, [] (point p) { return point{+p.y, +p.z, +p.x}; }}};
   
std::unordered_map<point, char> terrain_layer_tokenizing_reader::from_stream(
    std::istream& is)
{
    auto info = parse_header(is);

    auto result = std::unordered_map<point, char>{};

    auto row = 0;
    auto line = std::string{};
    while (std::getline(is, line))
    {
        if (line == "END LAYER") { return result; }
        
        parse_layer_line(line, row, info, result);

        ++row;
    }

    throw bad_layer_exception{};
}

void terrain_layer_tokenizing_reader::parse_layer_line(
    util::value_ref<std::string> line, 
    int const row,
    util::value_ref<layer_info> info, 
    std::unordered_map<point, char>& result)
{
    for (auto const i : util::sequence(0, static_cast<int>(line.size())))
    {
        if (!std::isspace(line[i]))
        {
            auto const p = point{info.origin.x + i, 
                                 info.origin.y - row, 
                                 info.depth};

            auto const rotated_p = transformers.at(info.normal)(p);

            result.emplace(rotated_p, line[i]);
        }
    }
}

terrain_layer_tokenizing_reader::layer_info 
    terrain_layer_tokenizing_reader::parse_header(std::istream& is) const
{
    auto line = std::string{};
    std::getline(is, line);
    
    auto const i = line.find(begin_layer_token);
    if (i == std::string::npos)
    {
        throw bad_layer_exception{};
    }
        
    auto encoded_info = line.substr(i + begin_layer_token.length());

    boost::algorithm::trim(encoded_info);

    return parse_layer_info(encoded_info);
}

terrain_layer_tokenizing_reader::layer_info 
    terrain_layer_tokenizing_reader::parse_layer_info(
        util::value_ref<std::string> s) const
{
    auto tokens = util::tokenize(s, ";");

    auto const dir = parse_layer_normal(tokens[0]);

    auto const depth = parse_layer_depth(tokens[1]);

    auto const origin = parse_layer_origin(tokens[2]);

    return {dir, depth, {origin.x, origin.y}};
}

block_face terrain_layer_tokenizing_reader::parse_layer_normal(
    util::value_ref<std::string> s) const
{
    auto const i = s.find(':');
    if (i == std::string::npos)
    {
        throw bad_layer_exception{};
    }

    auto encoded_direction = s.substr(i + 1);

    boost::algorithm::trim(encoded_direction);

    return formatted_directions.at(encoded_direction);
}

int terrain_layer_tokenizing_reader::parse_layer_depth(
    util::value_ref<std::string> s) const
{
    auto const i = s.find(':');
    if (i == std::string::npos)
    {
        throw bad_layer_exception{};
    }

    auto encoded_depth = s.substr(i + 1);

    boost::algorithm::trim(encoded_depth);

    return std::stoi(encoded_depth);
}

terrain_layer_tokenizing_reader::layer_origin 
    terrain_layer_tokenizing_reader::parse_layer_origin(
        util::value_ref<std::string> s) const
{
    auto const i = s.find(':');
    if (i == std::string::npos)
    {
        throw bad_layer_exception{};
    }

    auto encoded_origin = s.substr(i + 1);

    auto coordinates = util::tokenize(encoded_origin, ",");

    boost::algorithm::trim(coordinates[0]);

    boost::algorithm::trim(coordinates[1]);

    return {std::stoi(coordinates[0]), std::stoi(coordinates[1])};
}

} }
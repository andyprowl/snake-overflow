#pragma once

#include "snake_overflow/serialization/terrain_layer_reader.hpp"

namespace snake_overflow
{

enum class block_face;

}

namespace snake_overflow { namespace serialization
{

class terrain_layer_tokenizing_reader : public terrain_layer_reader
{

public:

    virtual std::unordered_map<point, char> from_stream(
        std::istream& is) override;

private:

    struct layer_info;
    struct layer_origin;

private:

    void parse_layer_line(util::value_ref<std::string> line, 
                          int row,
                          util::value_ref<layer_info> info, 
                          std::unordered_map<point, char>& result);

    layer_info parse_header(std::istream& is) const;

    layer_info parse_layer_info(util::value_ref<std::string> s) const;

    block_face parse_layer_normal(util::value_ref<std::string> s) const;

    int parse_layer_depth(util::value_ref<std::string> s) const;

    layer_origin parse_layer_origin(util::value_ref<std::string> s) const;

};

} }
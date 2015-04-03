#include "stdafx.hpp"

#include "snake_overflow/serialization/block_type.hpp"

namespace snake_overflow { namespace serialization
{

block_type::block_type(std::string texture, 
                       util::value_ref<rgba_color> color,
                       bool const is_solid)
    : texture(std::move(texture))
    , color{color}
    , is_solid{is_solid}
{
}

} }
#pragma once

namespace snake_overflow { namespace game_logic
{

enum class block_face
{
    front,
    back,
    left,
    right,
    top,
    bottom
};

block_face get_opposite_block_face(block_face s);

} }
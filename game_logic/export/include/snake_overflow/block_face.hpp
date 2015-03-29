#pragma once

namespace snake_overflow
{

struct point;

enum class block_face
{
    front,
    back,
    left,
    right,
    top,
    bottom
};

block_face get_opposite_face(block_face s);

point get_face_normal(block_face s);

}
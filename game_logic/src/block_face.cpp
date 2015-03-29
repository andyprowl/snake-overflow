#include "stdafx.hpp"

#include "snake_overflow/block_face.hpp"
#include "snake_overflow/point.hpp"
#include <cassert>

namespace snake_overflow
{

block_face get_opposite_face(block_face const s)
{
    switch (s)
    {
        case block_face::front: { return block_face::back; }
        
        case block_face::back: { return block_face::front; }
        
        case block_face::left: { return block_face::right; }
        
        case block_face::right: { return block_face::left; }
        
        case block_face::top: { return block_face::bottom; }
        
        case block_face::bottom: { return block_face::top; }
        
        default: assert(false); { return block_face::front; }
    }
}

point get_face_normal(block_face const s)
{
    switch (s)
    {
        case block_face::front: { return {0, -1, 0}; }
        
        case block_face::back: { return {0, +1, 0}; }
        
        case block_face::left: { return {-1, 0, 0}; }
        
        case block_face::right: { return {+1, 0, 0}; }
        
        case block_face::top: { return {0, 0, +1}; }
        
        case block_face::bottom: { return {0, 0, -1}; }
        
        default: assert(false); { return {0, 0, 0}; }
    }
}

}
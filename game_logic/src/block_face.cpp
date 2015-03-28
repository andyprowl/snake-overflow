#include "stdafx.hpp"

#include "snake_overflow/game_logic/block_face.hpp"
#include <cassert>

namespace snake_overflow { namespace game_logic
{

block_face get_opposite_block_face(block_face const s)
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

} }
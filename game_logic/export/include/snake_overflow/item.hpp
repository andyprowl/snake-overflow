#pragma once

#include <memory>

namespace snake_overflow
{

struct position;

class snake;
class terrain;

class item
{

public:

    virtual ~item() = default;

    virtual position get_position() const = 0;

    // This returns a unique pointer to itself: picking an item may mean
    // removing it from the terrain that owns it, therefore causing its
    // destruction. If a client needs to do something with the item, it needs to 
    // keep it alive after picking. If, upon picking, the itemwill not be 
    // removed from the terrain, a null unique pointer will be returned.
    virtual std::unique_ptr<item> pick(snake& s) = 0;

    virtual void age() = 0;

};

}
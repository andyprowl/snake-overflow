#pragma once

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

    virtual void pick(snake& s) = 0;

};

}
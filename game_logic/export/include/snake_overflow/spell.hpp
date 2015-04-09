#pragma once

namespace snake_overflow
{

class snake;

class spell
{

public:

    virtual ~spell() = default;

    virtual void affect(snake& s) = 0;

};

}
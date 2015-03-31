#pragma once

#include "snake_overflow/item.hpp"
#include "snake_overflow/position.hpp"

namespace snake_overflow
{

class fruit : public item
{

public:

    fruit(position placement, int nutrition_value);

    virtual position get_position() const override;

    virtual void pick(snake& s) override;

public:

    int nutrition_value;

private:

    position placement;

};

}
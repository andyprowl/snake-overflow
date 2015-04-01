#pragma once

#include "snake_overflow/item.hpp"

namespace snake_overflow { namespace testing
{

class fake_item : public item
{

public:

    fake_item(util::value_ref<position> pos)
        : placement{pos}
    {
    }

    virtual position get_position() const override
    {
        return placement;
    }

    virtual void pick(snake&) override
    {
    }

private:

    position placement;

};

} }
#pragma once

#include "snake_overflow/item.hpp"

namespace snake_overflow { namespace testing
{

class item_picked_exception : public virtual std::exception
{
};

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
        throw item_picked_exception{};
    }

    virtual void age() override
    {
        ++(this->item_age);
    }

public:

    position placement;

    int item_age = 0;

};

} }
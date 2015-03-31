#pragma once

namespace snake_overflow
{

struct position;

class item_position_picker
{

public:

    virtual ~item_position_picker() = default;

    virtual position pick_item_position() const = 0;

};

}
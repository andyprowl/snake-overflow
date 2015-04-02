#pragma once

#include "snake_overflow/consumable_item.hpp"

namespace snake_overflow
{

class diet_pill : public consumable_item
{

public:

    diet_pill(position placement, game& parent_game, int slim_power);

public:

    int slim_power;

private:

    virtual void handle_picking(snake& s) override;

    void make_snake_shrink_by_slim_power(snake& s) const;

};

}
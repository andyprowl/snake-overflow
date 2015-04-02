#pragma once

#include "snake_overflow/item.hpp"
#include "snake_overflow/position.hpp"

namespace snake_overflow
{

class game;

class consumable_item : public item
{

public:

    consumable_item(position placement, game& parent_game);

    virtual position get_position() const override final;

    virtual void pick(snake& s) override final;

private:

    virtual void handle_picking(snake& s) = 0;

    void remove_from_terrain_and_cause_self_destruction();

protected:

    position placement;

    game& parent_game;

};

}
#pragma once

#include "snake_overflow/item.hpp"
#include "snake_overflow/item_lifetime.hpp"
#include "snake_overflow/position.hpp"

namespace snake_overflow
{

class game;

class consumable_item : public item
{

public:

    consumable_item(position placement, game& parent_game, int lifetime);

    virtual position get_position() const override final;

    virtual void pick(snake& s) override final;

    virtual void age() override final;

    void remove_from_terrain_and_cause_self_destruction();

public:

    item_lifetime lifetime;

private:

    virtual void handle_picking(snake& s) = 0;

protected:

    position placement;

    game& parent_game;

};

}
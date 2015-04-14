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

    virtual std::unique_ptr<item> pick(snake& s) override final;

    virtual void age() override final;

public:

    item_lifetime lifetime;

private:

    friend class item_lifetime;

private:

    virtual void handle_picking(snake& s) = 0;

    std::unique_ptr<item> remove_from_terrain();

protected:

    position placement;

    game& parent_game;

};

}
#pragma once

#include "snake_overflow/item.hpp"
#include "snake_overflow/position.hpp"

namespace snake_overflow
{

class game;

class fruit : public item
{

public:

    fruit(position placement, game& parent_game, int nutrition_value);

    virtual position get_position() const override;

    virtual void pick(snake& s) override;

public:

    int nutrition_value;

private:

    void make_snake_grow_by_nutrition_value(snake& s) const;

    void add_nutrition_value_to_game_score() const;

    void remove_from_terrain_and_cause_self_destruction();

private:

    position placement;

    game& parent_game;

};

}
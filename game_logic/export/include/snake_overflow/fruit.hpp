#pragma once

#include "snake_overflow/consumable_item.hpp"

namespace snake_overflow
{

class fruit : public consumable_item
{

public:

    fruit(position placement, game& parent_game, int nutrition_value);
    
public:

    int nutrition_value;

private:

    virtual void handle_picking(snake& s) override;

    void make_snake_grow_by_nutrition_value(snake& s) const;

    void add_nutrition_value_to_game_score() const;

};

}
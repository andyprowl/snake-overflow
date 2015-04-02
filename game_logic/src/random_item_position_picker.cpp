#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/random_item_position_picker.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow
{

random_item_position_picker::random_item_position_picker(terrain& world)
    : world{world}
    , valid_positions(world.get_all_free_item_positions())
{
}

position random_item_position_picker::pick_item_position() const
{
    auto const max_index = static_cast<int>(valid_positions.size()) - 1;

    auto const index = this->random_generator.generate(0, max_index);

    return this->valid_positions[index];
}

}
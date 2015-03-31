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
    , normal_distribution{0, static_cast<int>(valid_positions.size())}
{
}

position random_item_position_picker::pick_item_position() const
{
    auto const index = this->normal_distribution(this->random_generator);

    return this->valid_positions[index];
}

}
#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/random_item_position_picker.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow
{

random_item_position_picker::random_item_position_picker(terrain& world)
    : world{world}
    , valid_positions(compute_valid_positions())
    , normal_distribution{0, static_cast<int>(valid_positions.size())}
{
}

std::vector<position> random_item_position_picker::get_valid_positions() const
{
    return this->valid_positions;
}

position random_item_position_picker::pick_item_position() const
{
    auto const index = this->normal_distribution(this->random_generator);

    return this->valid_positions[index];
}

std::vector<position> 
    random_item_position_picker::compute_valid_positions() const
{
    auto const blocks = this->world.get_blocks();

    auto valid_positions = std::vector<position>{};

    for (auto const b : blocks)
    {
        validate_block(b, valid_positions);
    }

    return valid_positions;
}

void random_item_position_picker::validate_block(
    util::value_ref<block> b, 
    std::vector<position>& valid_positions) const
{
    add_position_if_valid({b.origin, block_face::front}, valid_positions);

    add_position_if_valid({b.origin, block_face::back}, valid_positions);

    add_position_if_valid({b.origin, block_face::left}, valid_positions);

    add_position_if_valid({b.origin, block_face::right}, valid_positions);

    add_position_if_valid({b.origin, block_face::top}, valid_positions);

    add_position_if_valid({b.origin, block_face::bottom}, valid_positions);
}

void random_item_position_picker::add_position_if_valid(
    util::value_ref<position> pos,
    std::vector<position>& valid_positions) const
{
    auto const face_normal = get_face_normal(pos.face);

    auto const adjacent_location = pos.location + face_normal;

    auto const has_solid_neighbor = this->world.contains_solid_block(
        adjacent_location);

    if (!has_solid_neighbor)
    {
        valid_positions.push_back(pos);
    }
}

}
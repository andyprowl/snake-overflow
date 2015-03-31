#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/item_spawner.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow
{

item_spawner::item_spawner(terrain& world)
    : world{world}
{
}

std::vector<position> item_spawner::get_valid_positions() const
{
    auto const blocks = this->world.get_blocks();

    auto valid_positions = std::vector<position>{};

    for (auto const b : blocks)
    {
        validate_block(b, valid_positions);
    }

    return valid_positions;
}

void item_spawner::validate_block(
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

void item_spawner::add_position_if_valid(
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
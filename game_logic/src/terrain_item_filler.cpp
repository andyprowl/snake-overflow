#include "stdafx.hpp"

#include "snake_overflow/item_spawner.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_item_filler.hpp"
#include <algorithm>

namespace snake_overflow
{

terrain_item_filler::terrain_item_filler(item_spawner& spawner)
    : spawner{spawner}
    , minimum_load_factor{0.0}
    , maximum_load_factor{0.25}
    , total_num_of_item_positions{get_total_num_of_item_positions_on_terrain()}
    , minimum_num_of_items{-1}
    , maximum_num_of_items{-1}
{
    recompute_range_of_allowed_num_of_items();
}

void terrain_item_filler::fill_terrain()
{
    auto const total_num_of_items = get_num_of_items_currently_on_terrain();
    if (total_num_of_items > this->maximum_num_of_items)
    {
        return;
    }

    auto min_num_of_items_to_spawn = 
        std::max(0, this->minimum_num_of_items - total_num_of_items);

    auto max_num_of_items_to_spawn = 
        this->maximum_num_of_items - total_num_of_items;

    auto num_of_items_to_spawn = random_generator.generate(
        min_num_of_items_to_spawn, 
        max_num_of_items_to_spawn);

    this->spawner.spawn(num_of_items_to_spawn);
}

double terrain_item_filler::get_minimum_load_factor() const
{
    return this->minimum_load_factor;
}

double terrain_item_filler::get_maximum_load_factor() const
{
    return this->maximum_load_factor;
}

void terrain_item_filler::set_minimum_load_factor(double const factor)
{
    if ((factor < 0.0) || (factor > this->maximum_load_factor))
    {
        throw bad_load_factor_range_exception{};
    }

    this->minimum_load_factor = factor;

    recompute_range_of_allowed_num_of_items();
}

void terrain_item_filler::set_maximum_load_factor(double const factor)
{
    if ((factor > get_maximum_load_factor_upper_limit()) || 
        (factor < this->minimum_load_factor))
    {
        throw bad_load_factor_range_exception{};
    }

    this->maximum_load_factor = factor;

    recompute_range_of_allowed_num_of_items();
}

double terrain_item_filler::get_maximum_load_factor_upper_limit() const
{
    return 0.50;
}

terrain& terrain_item_filler::get_terrain() const
{
    return this->spawner.ground;
}

int terrain_item_filler::get_num_of_items_currently_on_terrain() const
{
    auto& t = get_terrain();

    return t.get_num_of_items();
}

int terrain_item_filler::get_total_num_of_item_positions_on_terrain() const
{
    auto& t = get_terrain();

    return static_cast<int>(t.get_all_free_item_positions().size());
}

void terrain_item_filler::recompute_range_of_allowed_num_of_items()
{
    this->total_num_of_item_positions = 
        get_total_num_of_item_positions_on_terrain();

    this->minimum_num_of_items = 
        static_cast<int>(this->minimum_load_factor * 
                         this->total_num_of_item_positions);

    this->maximum_num_of_items = 
        static_cast<int>(this->maximum_load_factor * 
                         this->total_num_of_item_positions);
}

}
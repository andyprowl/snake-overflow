#pragma once

#include "snake_overflow/random_integer_generator.hpp"
#include "snake_overflow/terrain_item_filler.hpp"
#include <memory>

namespace snake_overflow
{

class terrain;

class bad_load_factor_range_exception : public virtual std::exception
{
};

class load_driven_terrain_item_filler : public terrain_item_filler
{

public:

    load_driven_terrain_item_filler(std::unique_ptr<item_spawner>&& spawner);

    void fill_terrain();

    double get_minimum_load_factor() const;

    double get_maximum_load_factor() const;

    void set_minimum_load_factor(double factor);

    void set_maximum_load_factor(double factor);

    double get_maximum_load_factor_upper_limit() const;

private:

    terrain& get_terrain() const;

    int get_num_of_items_currently_on_terrain() const;

    int get_total_num_of_item_positions_on_terrain() const;

    void recompute_range_of_allowed_num_of_items();

private:

    std::unique_ptr<item_spawner> owned_spawner;
    
    int total_num_of_item_positions;

    double minimum_load_factor;
    
    double maximum_load_factor;

    int minimum_num_of_items;

    int maximum_num_of_items;

    random_integer_generator random_generator;

};

}
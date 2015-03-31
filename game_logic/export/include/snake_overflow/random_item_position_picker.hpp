#pragma once

#include "snake_overflow/item_position_picker.hpp"
#include "util/value_ref.hpp"
#include <random>
#include <vector>

namespace snake_overflow
{

struct block;
struct position;

class terrain;

class random_item_position_picker : public item_position_picker
{

public:

    random_item_position_picker(terrain& world);

    virtual position pick_item_position() const override;

private:

    terrain& world;

    std::vector<position> valid_positions;

    std::random_device device;
    
    mutable std::mt19937 random_generator{device()};

    std::uniform_int_distribution<> normal_distribution;

};

}
#pragma once

#include "snake_overflow/item_position_picker.hpp"
#include "snake_overflow/random_integer_generator.hpp"
#include "util/value_ref.hpp"
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

    random_integer_generator random_generator;

};

}
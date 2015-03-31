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

    std::vector<position> get_valid_positions() const;

    virtual position pick_item_position() const override;

private:

    std::vector<position> compute_valid_positions() const;

    void validate_block(util::value_ref<block> b, 
                        std::vector<position>& valid_positions) const;

    void add_position_if_valid(
        util::value_ref<position> pos,
        std::vector<position>& valid_positions) const;

private:

    terrain& world;

    std::vector<position> valid_positions;

    std::random_device device;
    
    mutable std::mt19937 random_generator{device()};

    std::uniform_int_distribution<> normal_distribution;

};

}
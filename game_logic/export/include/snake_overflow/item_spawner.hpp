#pragma once

#include "util/value_ref.hpp"
#include <vector>

namespace snake_overflow
{

struct block;
struct position;

class terrain;

class item_spawner
{

public:

    item_spawner(terrain& world);

    std::vector<position> get_valid_positions() const;

private:

    void validate_block(util::value_ref<block> b, 
                        std::vector<position>& valid_positions) const;

    void add_position_if_valid(
        util::value_ref<position> pos,
        std::vector<position>& valid_positions) const;

private:

    terrain& world;

};

}
#pragma once

#include "snake_overflow/game_logic/block.hpp"
#include "util/noexcept.hpp"
#include "util/value_ref.hpp"
#include <vector>

namespace snake_overflow { namespace game_logic
{

enum class direction;

struct block;
struct position;

class territory
{

public:
    
    std::vector<block> get_blocks() const;

    void add_block(util::value_ref<block> b);

    position compute_step_target(util::value_ref<position> start,
                                 util::value_ref<math::point3d> dir) const;

private:

    std::vector<block> blocks;

};

} }
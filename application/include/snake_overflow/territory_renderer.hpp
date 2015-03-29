#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

struct block;

class territory;

class territory_renderer
{

public:

    territory_renderer(float block_size);

    void render(territory& t) const;

private:

    void render_block(util::value_ref<block> b) const;

private:

    float block_size;

};

}
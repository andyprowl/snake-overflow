#include "stdafx.hpp"

#include "snake_overflow/game_logic/cube_builder.hpp"
#include "snake_overflow/game_logic/territory.hpp"
#include "snake_overflow/game_logic/block.hpp"
#include "math/point3d.hpp"

namespace snake_overflow { namespace game_logic { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class CubeBuilder : public Test
{

protected:

    territory t;

    cube_builder builder{t};

};

TEST_THAT(CubeBuilder,
     WHAT(AddCube),
     WHEN(GivenAnOriginBlockAndASideLength),
     THEN(AddsASeriesOfBlocksLaidOutAsACubeToTheTerritoryPassedAtConstruction))
{
    this->builder.add_cube({-1, 3, 4}, 3);

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(27u));
}

} } }
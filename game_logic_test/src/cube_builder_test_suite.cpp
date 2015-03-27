#include "stdafx.hpp"

#include "snake_overflow/game_logic/cube_builder.hpp"
#include "snake_overflow/game_logic/territory.hpp"

namespace snake_overflow { namespace game_logic { namespace testing
{

using ::testing::Test;

class CubeBuilder : public Test
{

protected:

    territory t;

    cube_builder builder{t};

};

/*
TEST_THAT(CubeBuilder,
     WHAT(AddCube),
     WHEN(GivenAnOriginBlockAndASideLength),
     THEN(AddsASeriesOfBlockLaidOutAsACubeWithThatCenterAndSideLength))
{
    builder.add_cube({0, 0, 0})
}*/

} } }
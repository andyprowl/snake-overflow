#include "stdafx.hpp"

#include "snake_overflow/game_logic/block.hpp"
#include "snake_overflow/game_logic/cube_builder.hpp"
#include "snake_overflow/game_logic/direction.hpp"
#include "snake_overflow/game_logic/position.hpp"
#include "snake_overflow/game_logic/territory.hpp"

namespace snake_overflow { namespace game_logic { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class Territory : public Test
{

protected:

    void create_cube_with_vertex_on_origin(int const side_length)
    {
        cube_builder builder{this->t};

        builder.add_cube({0, 0, 0}, side_length);
    }

    void verify_step(util::value_ref<position> start,
                     util::value_ref<math::point3d> dir,
                     util::value_ref<position> expected_result)
    {
        auto const pos = this->t.compute_step_target(start, dir);

        EXPECT_THAT(pos, Eq(expected_result));
    }

protected:

    territory t;

};

TEST_THAT(Territory,
     WHAT(GetBlocks),
     WHEN(ImmediatelyAfterDefaultConstruction),
     THEN(ReturnsAnEmptyCollectionOfBlocks))
{
    auto const blocks = this->t.get_blocks();

    EXPECT_TRUE(blocks.empty());
}

TEST_THAT(Territory,
     WHAT(AddBlock),
     WHEN(GivenABlockThatIsNotAlreadyPartOfTheTerritory),
     THEN(AddsTheBlockToTheTerritory))
{
    auto const b = block{{0, 1, 2}};

    this->t.add_block(b);

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));

    EXPECT_THAT(blocks[0], Eq(b));
}

TEST_THAT(Territory,
     WHAT(AddBlock),
     WHEN(GivenABlockThatIsAlreadyPartOfTheTerritory),
     THEN(DoesNotAddThatBlockAgain))
{
    auto const b = block{{0, 1, 2}};

    this->t.add_block(b);

    this->t.add_block(b);

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));
}

TEST_THAT(Territory,
     WHAT(ComputeStepTarget),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToXAndADirectionAlongX),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);
    auto const x = math::point3d::x_unit();

    verify_step({{1, 0, 1}, surface::front}, x, {{2, 0, 1}, surface::front});
    verify_step({{1, 0, 1}, surface::front}, -x, {{0, 0, 1}, surface::front});
    verify_step({{1, 3, 1}, surface::back}, x, {{2, 3, 1}, surface::back});
    verify_step({{1, 3, 1}, surface::back}, -x, {{0, 3, 1}, surface::back});
    verify_step({{1, 1, 3}, surface::top}, x, {{2, 1, 3}, surface::top});
    verify_step({{1, 1, 3}, surface::top}, -x, {{0, 1, 3}, surface::top});
    verify_step({{1, 1, 0}, surface::bottom}, x, {{2, 1, 0}, surface::bottom});
    verify_step({{1, 1, 0}, surface::bottom}, -x, {{0, 1, 0}, surface::bottom});
}

TEST_THAT(Territory,
     WHAT(ComputeStepTarget),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToYAndADirectionAlongY),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);
    auto const y = math::point3d::y_unit();

    verify_step({{0, 1, 1}, surface::left}, y, {{0, 2, 1}, surface::left});
    verify_step({{0, 1, 1}, surface::left}, -y, {{0, 0, 1}, surface::left});
    verify_step({{3, 1, 1}, surface::right}, y, {{3, 2, 1}, surface::right});
    verify_step({{3, 1, 1}, surface::right}, -y, {{3, 0, 1}, surface::right});
    verify_step({{1, 1, 3}, surface::top}, y, {{1, 2, 3}, surface::top});
    verify_step({{1, 1, 3}, surface::top}, -y, {{1, 0, 3}, surface::top});
    verify_step({{1, 1, 0}, surface::bottom}, y, {{1, 2, 0}, surface::bottom});
    verify_step({{1, 1, 0}, surface::bottom}, -y, {{1, 0, 0}, surface::bottom});
}

TEST_THAT(Territory,
     WHAT(ComputeStepTarget),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToZAndADirectionAlongZ),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);
    auto const z = math::point3d::z_unit();

    verify_step({{1, 0, 1}, surface::front}, z, {{1, 0, 2}, surface::front});
    verify_step({{1, 0, 1}, surface::front}, -z, {{1, 0, 0}, surface::front});
    verify_step({{1, 3, 1}, surface::back}, z, {{1, 3, 2}, surface::back});
    verify_step({{1, 3, 1}, surface::back}, -z, {{1, 3, 0}, surface::back});
    verify_step({{0, 1, 1}, surface::left}, z, {{0, 1, 2}, surface::left});
    verify_step({{0, 1, 1}, surface::left}, -z, {{0, 1, 0}, surface::left});
    verify_step({{3, 1, 1}, surface::right}, z, {{3, 1, 2}, surface::right});
    verify_step({{3, 1, 1}, surface::right}, -z, {{3, 1, 0}, surface::right});
}

} } }
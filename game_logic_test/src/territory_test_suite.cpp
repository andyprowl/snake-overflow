#include "stdafx.hpp"

#include "snake_overflow/game_logic/block.hpp"
#include "snake_overflow/game_logic/cube_builder.hpp"
#include "snake_overflow/game_logic/direction.hpp"
#include "snake_overflow/game_logic/dynamics.hpp"
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

    void verify_step(util::value_ref<dynamics> d,
                     util::value_ref<dynamics> expected_result)
    {
        EXPECT_THAT(this->t.compute_step(d), Eq(expected_result));
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

    auto const px = direction{cartesian_axis::x, orientation::positive};
    auto const nx = direction{cartesian_axis::x, orientation::negative};

    verify_step({{{1, 0, 1}, surface::front}, px}, 
                {{{2, 0, 1}, surface::front}, px});

    verify_step({{{1, 0, 1}, surface::front}, nx}, 
                {{{0, 0, 1}, surface::front}, nx});

    verify_step({{{1, 3, 1}, surface::back}, px}, 
                {{{2, 3, 1}, surface::back}, px});

    verify_step({{{1, 3, 1}, surface::back}, nx}, 
                {{{0, 3, 1}, surface::back}, nx});

    verify_step({{{1, 1, 3}, surface::top}, px}, 
                {{{2, 1, 3}, surface::top}, px});

    verify_step({{{1, 1, 3}, surface::top}, nx}, 
                {{{0, 1, 3}, surface::top}, nx});

    verify_step({{{1, 1, 0}, surface::bottom}, px}, 
                {{{2, 1, 0}, surface::bottom}, px});

    verify_step({{{1, 1, 0}, surface::bottom}, nx}, 
                {{{0, 1, 0}, surface::bottom}, nx});
}

TEST_THAT(Territory,
     WHAT(ComputeStepTarget),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToYAndADirectionAlongY),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);

    auto const py = direction{cartesian_axis::y, orientation::positive};
    auto const ny = direction{cartesian_axis::y, orientation::negative};

    verify_step({{{0, 1, 1}, surface::left}, py}, 
                {{{0, 2, 1}, surface::left}, py});

    verify_step({{{0, 1, 1}, surface::left}, ny}, 
                {{{0, 0, 1}, surface::left}, ny});

    verify_step({{{3, 1, 1}, surface::right}, py}, 
                {{{3, 2, 1}, surface::right}, py});

    verify_step({{{3, 1, 1}, surface::right}, ny}, 
                {{{3, 0, 1}, surface::right}, ny});

    verify_step({{{1, 1, 3}, surface::top}, py}, 
                {{{1, 2, 3}, surface::top}, py});

    verify_step({{{1, 1, 3}, surface::top}, ny}, 
                {{{1, 0, 3}, surface::top}, ny});

    verify_step({{{1, 1, 0}, surface::bottom}, py}, 
                {{{1, 2, 0}, surface::bottom}, py});

    verify_step({{{1, 1, 0}, surface::bottom}, ny}, 
                {{{1, 0, 0}, surface::bottom}, ny});
}

TEST_THAT(Territory,
     WHAT(ComputeStepTarget),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToZAndADirectionAlongZ),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);

    auto const pz = direction{cartesian_axis::z, orientation::positive};
    auto const nz = direction{cartesian_axis::z, orientation::negative};

    verify_step({{{1, 0, 1}, surface::front}, pz}, 
                {{{1, 0, 2}, surface::front}, pz});
    
    verify_step({{{1, 0, 1}, surface::front}, nz}, 
                {{{1, 0, 0}, surface::front}, nz});
    
    verify_step({{{1, 3, 1}, surface::back}, pz}, 
                {{{1, 3, 2}, surface::back}, pz});
    
    verify_step({{{1, 3, 1}, surface::back}, nz}, 
                {{{1, 3, 0}, surface::back}, nz});
    
    verify_step({{{0, 1, 1}, surface::left}, pz}, 
                {{{0, 1, 2}, surface::left}, pz});
    
    verify_step({{{0, 1, 1}, surface::left}, nz}, 
                {{{0, 1, 0}, surface::left}, nz});
    
    verify_step({{{3, 1, 1}, surface::right}, pz}, 
                {{{3, 1, 2}, surface::right}, pz});
    
    verify_step({{{3, 1, 1}, surface::right}, nz}, 
                {{{3, 1, 0}, surface::right}, nz});
}

} } }
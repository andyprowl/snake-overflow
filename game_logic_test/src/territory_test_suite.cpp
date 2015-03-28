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
     WHAT(ComputeStep),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToXAndADirectionAlongX),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{{1, 0, 1}, surface::front}, direction::positive_x()}, 
                {{{2, 0, 1}, surface::front}, direction::positive_x()});

    verify_step({{{1, 0, 1}, surface::front}, direction::negative_x()}, 
                {{{0, 0, 1}, surface::front}, direction::negative_x()});

    verify_step({{{1, 3, 1}, surface::back}, direction::positive_x()}, 
                {{{2, 3, 1}, surface::back}, direction::positive_x()});

    verify_step({{{1, 3, 1}, surface::back}, direction::negative_x()}, 
                {{{0, 3, 1}, surface::back}, direction::negative_x()});

    verify_step({{{1, 1, 3}, surface::top}, direction::positive_x()}, 
                {{{2, 1, 3}, surface::top}, direction::positive_x()});

    verify_step({{{1, 1, 3}, surface::top}, direction::negative_x()}, 
                {{{0, 1, 3}, surface::top}, direction::negative_x()});

    verify_step({{{1, 1, 0}, surface::bottom}, direction::positive_x()}, 
                {{{2, 1, 0}, surface::bottom}, direction::positive_x()});

    verify_step({{{1, 1, 0}, surface::bottom}, direction::negative_x()}, 
                {{{0, 1, 0}, surface::bottom}, direction::negative_x()});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToYAndADirectionAlongY),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{{0, 1, 1}, surface::left}, direction::positive_y()}, 
                {{{0, 2, 1}, surface::left}, direction::positive_y()});

    verify_step({{{0, 1, 1}, surface::left}, direction::negative_y()}, 
                {{{0, 0, 1}, surface::left}, direction::negative_y()});

    verify_step({{{3, 1, 1}, surface::right}, direction::positive_y()}, 
                {{{3, 2, 1}, surface::right}, direction::positive_y()});

    verify_step({{{3, 1, 1}, surface::right}, direction::negative_y()}, 
                {{{3, 0, 1}, surface::right}, direction::negative_y()});

    verify_step({{{1, 1, 3}, surface::top}, direction::positive_y()}, 
                {{{1, 2, 3}, surface::top}, direction::positive_y()});

    verify_step({{{1, 1, 3}, surface::top}, direction::negative_y()}, 
                {{{1, 0, 3}, surface::top}, direction::negative_y()});

    verify_step({{{1, 1, 0}, surface::bottom}, direction::positive_y()}, 
                {{{1, 2, 0}, surface::bottom}, direction::positive_y()});

    verify_step({{{1, 1, 0}, surface::bottom}, direction::negative_y()}, 
                {{{1, 0, 0}, surface::bottom}, direction::negative_y()});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToZAndADirectionAlongZ),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{{1, 0, 1}, surface::front}, direction::positive_z()}, 
                {{{1, 0, 2}, surface::front}, direction::positive_z()});
    
    verify_step({{{1, 0, 1}, surface::front}, direction::negative_z()}, 
                {{{1, 0, 0}, surface::front}, direction::negative_z()});
    
    verify_step({{{1, 3, 1}, surface::back}, direction::positive_z()}, 
                {{{1, 3, 2}, surface::back}, direction::positive_z()});
    
    verify_step({{{1, 3, 1}, surface::back}, direction::negative_z()}, 
                {{{1, 3, 0}, surface::back}, direction::negative_z()});
    
    verify_step({{{0, 1, 1}, surface::left}, direction::positive_z()}, 
                {{{0, 1, 2}, surface::left}, direction::positive_z()});
    
    verify_step({{{0, 1, 1}, surface::left}, direction::negative_z()}, 
                {{{0, 1, 0}, surface::left}, direction::negative_z()});
    
    verify_step({{{3, 1, 1}, surface::right}, direction::positive_z()}, 
                {{{3, 1, 2}, surface::right}, direction::positive_z()});
    
    verify_step({{{3, 1, 1}, surface::right}, direction::negative_z()}, 
                {{{3, 1, 0}, surface::right}, direction::negative_z()});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionOnTheEdgeOfASurfaceParallelToXAndADirectionAlongX),
     THEN(ReturnsAPositionOnTheAdjacentSurfaceWithAppropriateDirection))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{{3, 0, 1}, surface::front}, direction::positive_x()}, 
                {{{3, 0, 1}, surface::right}, direction::positive_y()});

    verify_step({{{0, 0, 1}, surface::front}, direction::negative_x()}, 
                {{{0, 0, 1}, surface::left}, direction::positive_y()});

    verify_step({{{3, 3, 1}, surface::back}, direction::positive_x()}, 
                {{{3, 3, 1}, surface::right}, direction::negative_y()});

    verify_step({{{0, 3, 1}, surface::back}, direction::negative_x()}, 
                {{{0, 3, 1}, surface::left}, direction::negative_y()});

    verify_step({{{3, 1, 3}, surface::top}, direction::positive_x()}, 
                {{{3, 1, 3}, surface::right}, direction::negative_z()});

    verify_step({{{0, 1, 3}, surface::top}, direction::negative_x()}, 
                {{{0, 1, 3}, surface::left}, direction::negative_z()});

    verify_step({{{3, 1, 0}, surface::bottom}, direction::positive_x()}, 
                {{{3, 1, 0}, surface::right}, direction::positive_z()});

    verify_step({{{0, 1, 0}, surface::bottom}, direction::negative_x()}, 
                {{{0, 1, 0}, surface::left}, direction::positive_z()});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionOnTheEdgeOfASurfaceParallelToYAndADirectionAlongY),
     THEN(ReturnsAPositionOnTheAdjacentSurfaceWithAppropriateDirection))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{{0, 3, 1}, surface::left}, direction::positive_y()}, 
                {{{0, 3, 1}, surface::back}, direction::positive_x()});

    verify_step({{{0, 0, 1}, surface::left}, direction::negative_y()}, 
                {{{0, 0, 1}, surface::front}, direction::positive_x()});

    verify_step({{{3, 3, 1}, surface::right}, direction::positive_y()}, 
                {{{3, 3, 1}, surface::back}, direction::negative_x()});

    verify_step({{{3, 0, 1}, surface::right}, direction::negative_y()}, 
                {{{3, 0, 1}, surface::front}, direction::negative_x()});

    verify_step({{{1, 3, 3}, surface::top}, direction::positive_y()}, 
                {{{1, 3, 3}, surface::back}, direction::negative_z()});

    verify_step({{{1, 0, 3}, surface::top}, direction::negative_y()}, 
                {{{1, 0, 3}, surface::front}, direction::negative_z()});

    verify_step({{{1, 3, 0}, surface::bottom}, direction::positive_y()}, 
                {{{1, 3, 0}, surface::back}, direction::positive_z()});
    
    verify_step({{{1, 0, 0}, surface::bottom}, direction::negative_y()}, 
                {{{1, 0, 0}, surface::front}, direction::positive_z()});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionOnTheEdgeOfASurfaceParallelToZAndADirectionAlongZ),
     THEN(ReturnsAPositionOnTheAdjacentSurfaceWithAppropriateDirection))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{{1, 0, 3}, surface::front}, direction::positive_z()}, 
                {{{1, 0, 3}, surface::top}, direction::positive_y()});

    verify_step({{{1, 0, 0}, surface::front}, direction::negative_z()}, 
                {{{1, 0, 0}, surface::bottom}, direction::positive_y()});

    verify_step({{{1, 3, 3}, surface::back}, direction::positive_z()}, 
                {{{1, 3, 3}, surface::top}, direction::negative_y()});

    verify_step({{{1, 3, 0}, surface::back}, direction::negative_z()}, 
                {{{1, 3, 0}, surface::bottom}, direction::negative_y()});

    verify_step({{{0, 1, 3}, surface::left}, direction::positive_z()}, 
                {{{0, 1, 3}, surface::top}, direction::positive_x()});

    verify_step({{{0, 1, 0}, surface::left}, direction::negative_z()}, 
                {{{0, 1, 0}, surface::bottom}, direction::positive_x()});

    verify_step({{{3, 1, 3}, surface::right}, direction::positive_z()}, 
                {{{3, 1, 3}, surface::top}, direction::negative_x()});

    verify_step({{{3, 1, 0}, surface::right}, direction::negative_z()}, 
                {{{3, 1, 0}, surface::bottom}, direction::negative_x()});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionOnTheEdgeOfASurfaceAndADirectionThatLeadsToATurnBlock),
     THEN(ReturnsAPositionOnTheAppropriateSurfaceOfThatBlock))
{
    create_cube_with_vertex_on_origin(4);

    this->t.add_block({{1, -1, 2}});

    verify_step({{{1, 0, 3}, surface::front}, direction::negative_z()}, 
                {{{1, -1, 2}, surface::top}, direction::negative_y()});

    this->t.add_block({{4, 3, 2}});

    verify_step({{{3, 2, 2}, surface::right}, direction::positive_y()}, 
                {{{4, 3, 2}, surface::front}, direction::positive_x()});

    this->t.add_block({{2, 4, 4}});

    verify_step({{{2, 3, 3}, surface::top}, direction::positive_y()}, 
                {{{2, 4, 4}, surface::front}, direction::positive_z()});
}

} } }
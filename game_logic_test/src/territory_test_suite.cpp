#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/cube_builder.hpp"
#include "snake_overflow/canonical_direction.hpp"
#include "snake_overflow/dynamics.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/territory.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class Territory : public Test
{

protected:

    void create_cube_with_vertex_on_origin(int const side_length)
    {
        cube_builder builder{this->t};

        builder.add_cube({0, 0, 0}, side_length, "texture.jpg");
    }

    void verify_step(util::value_ref<dynamics> d,
                     util::value_ref<dynamics> expected_result)
    {
        EXPECT_THAT(this->t.compute_step(d), Eq(expected_result));
    }

protected:

    territory t;

};

auto const positive_x_direction = canonical_direction::positive_x();
auto const negative_x_direction = canonical_direction::negative_x();
auto const positive_y_direction = canonical_direction::positive_y();
auto const negative_y_direction = canonical_direction::negative_y();
auto const positive_z_direction = canonical_direction::positive_z();
auto const negative_z_direction = canonical_direction::negative_z();

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
    auto const b = block{{0, 1, 2}, "texture.jpg"};

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
    auto const b = block{{0, 1, 2}, "texture.jpg"};

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

    verify_step({{1, 0, 1}, {block_face::front, positive_x_direction}}, 
                {{2, 0, 1}, {block_face::front, positive_x_direction}});

    verify_step({{1, 0, 1}, {block_face::front, negative_x_direction}}, 
                {{0, 0, 1}, {block_face::front, negative_x_direction}});

    verify_step({{1, 3, 1}, {block_face::back, positive_x_direction}}, 
                {{2, 3, 1}, {block_face::back, positive_x_direction}});

    verify_step({{1, 3, 1}, {block_face::back, negative_x_direction}}, 
                {{0, 3, 1}, {block_face::back, negative_x_direction}});

    verify_step({{1, 1, 3}, {block_face::top, positive_x_direction}}, 
                {{2, 1, 3}, {block_face::top, positive_x_direction}});

    verify_step({{1, 1, 3}, {block_face::top, negative_x_direction}}, 
                {{0, 1, 3}, {block_face::top, negative_x_direction}});

    verify_step({{1, 1, 0}, {block_face::bottom, positive_x_direction}}, 
                {{2, 1, 0}, {block_face::bottom, positive_x_direction}});

    verify_step({{1, 1, 0}, {block_face::bottom, negative_x_direction}}, 
                {{0, 1, 0}, {block_face::bottom, negative_x_direction}});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToYAndADirectionAlongY),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{0, 1, 1}, {block_face::left, positive_y_direction}}, 
                {{0, 2, 1}, {block_face::left, positive_y_direction}});

    verify_step({{0, 1, 1}, {block_face::left, negative_y_direction}}, 
                {{0, 0, 1}, {block_face::left, negative_y_direction}});

    verify_step({{3, 1, 1}, {block_face::right, positive_y_direction}}, 
                {{3, 2, 1}, {block_face::right, positive_y_direction}});

    verify_step({{3, 1, 1}, {block_face::right, negative_y_direction}}, 
                {{3, 0, 1}, {block_face::right, negative_y_direction}});

    verify_step({{1, 1, 3}, {block_face::top, positive_y_direction}}, 
                {{1, 2, 3}, {block_face::top, positive_y_direction}});

    verify_step({{1, 1, 3}, {block_face::top, negative_y_direction}}, 
                {{1, 0, 3}, {block_face::top, negative_y_direction}});

    verify_step({{1, 1, 0}, {block_face::bottom, positive_y_direction}}, 
                {{1, 2, 0}, {block_face::bottom, positive_y_direction}});

    verify_step({{1, 1, 0}, {block_face::bottom, negative_y_direction}}, 
                {{1, 0, 0}, {block_face::bottom, negative_y_direction}});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionInTheMiddleOfASurfaceParallelToZAndADirectionAlongZ),
     THEN(ReturnsAPositionOnTheSameSurfaceOfTheAppropriateAdjacentBlock))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{1, 0, 1}, {block_face::front, positive_z_direction}}, 
                {{1, 0, 2}, {block_face::front, positive_z_direction}});
    
    verify_step({{1, 0, 1}, {block_face::front, negative_z_direction}}, 
                {{1, 0, 0}, {block_face::front, negative_z_direction}});
    
    verify_step({{1, 3, 1}, {block_face::back, positive_z_direction}}, 
                {{1, 3, 2}, {block_face::back, positive_z_direction}});
    
    verify_step({{1, 3, 1}, {block_face::back, negative_z_direction}}, 
                {{1, 3, 0}, {block_face::back, negative_z_direction}});
    
    verify_step({{0, 1, 1}, {block_face::left, positive_z_direction}}, 
                {{0, 1, 2}, {block_face::left, positive_z_direction}});
    
    verify_step({{0, 1, 1}, {block_face::left, negative_z_direction}}, 
                {{0, 1, 0}, {block_face::left, negative_z_direction}});
    
    verify_step({{3, 1, 1}, {block_face::right, positive_z_direction}}, 
                {{3, 1, 2}, {block_face::right, positive_z_direction}});
    
    verify_step({{3, 1, 1}, {block_face::right, negative_z_direction}}, 
                {{3, 1, 0}, {block_face::right, negative_z_direction}});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionOnTheEdgeOfASurfaceParallelToXAndADirectionAlongX),
     THEN(ReturnsAPositionOnTheAdjacentSurfaceWithAppropriateDirection))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{3, 0, 1}, {block_face::front, positive_x_direction}}, 
                {{3, 0, 1}, {block_face::right, positive_y_direction}});

    verify_step({{0, 0, 1}, {block_face::front, negative_x_direction}}, 
                {{0, 0, 1}, {block_face::left, positive_y_direction}});

    verify_step({{3, 3, 1}, {block_face::back, positive_x_direction}}, 
                {{3, 3, 1}, {block_face::right, negative_y_direction}});

    verify_step({{0, 3, 1}, {block_face::back, negative_x_direction}}, 
                {{0, 3, 1}, {block_face::left, negative_y_direction}});

    verify_step({{3, 1, 3}, {block_face::top, positive_x_direction}}, 
                {{3, 1, 3}, {block_face::right, negative_z_direction}});

    verify_step({{0, 1, 3}, {block_face::top, negative_x_direction}}, 
                {{0, 1, 3}, {block_face::left, negative_z_direction}});

    verify_step({{3, 1, 0}, {block_face::bottom, positive_x_direction}}, 
                {{3, 1, 0}, {block_face::right, positive_z_direction}});

    verify_step({{0, 1, 0}, {block_face::bottom, negative_x_direction}}, 
                {{0, 1, 0}, {block_face::left, positive_z_direction}});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionOnTheEdgeOfASurfaceParallelToYAndADirectionAlongY),
     THEN(ReturnsAPositionOnTheAdjacentSurfaceWithAppropriateDirection))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{0, 3, 1}, {block_face::left, positive_y_direction}}, 
                {{0, 3, 1}, {block_face::back, positive_x_direction}});

    verify_step({{0, 0, 1}, {block_face::left, negative_y_direction}}, 
                {{0, 0, 1}, {block_face::front, positive_x_direction}});

    verify_step({{3, 3, 1}, {block_face::right, positive_y_direction}}, 
                {{3, 3, 1}, {block_face::back, negative_x_direction}});

    verify_step({{3, 0, 1}, {block_face::right, negative_y_direction}}, 
                {{3, 0, 1}, {block_face::front, negative_x_direction}});

    verify_step({{1, 3, 3}, {block_face::top, positive_y_direction}}, 
                {{1, 3, 3}, {block_face::back, negative_z_direction}});

    verify_step({{1, 0, 3}, {block_face::top, negative_y_direction}}, 
                {{1, 0, 3}, {block_face::front, negative_z_direction}});

    verify_step({{1, 3, 0}, {block_face::bottom, positive_y_direction}}, 
                {{1, 3, 0}, {block_face::back, positive_z_direction}});
    
    verify_step({{1, 0, 0}, {block_face::bottom, negative_y_direction}}, 
                {{1, 0, 0}, {block_face::front, positive_z_direction}});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionOnTheEdgeOfASurfaceParallelToZAndADirectionAlongZ),
     THEN(ReturnsAPositionOnTheAdjacentSurfaceWithAppropriateDirection))
{
    create_cube_with_vertex_on_origin(4);

    verify_step({{1, 0, 3}, {block_face::front, positive_z_direction}}, 
                {{1, 0, 3}, {block_face::top, positive_y_direction}});

    verify_step({{1, 0, 0}, {block_face::front, negative_z_direction}}, 
                {{1, 0, 0}, {block_face::bottom, positive_y_direction}});

    verify_step({{1, 3, 3}, {block_face::back, positive_z_direction}}, 
                {{1, 3, 3}, {block_face::top, negative_y_direction}});

    verify_step({{1, 3, 0}, {block_face::back, negative_z_direction}}, 
                {{1, 3, 0}, {block_face::bottom, negative_y_direction}});

    verify_step({{0, 1, 3}, {block_face::left, positive_z_direction}}, 
                {{0, 1, 3}, {block_face::top, positive_x_direction}});

    verify_step({{0, 1, 0}, {block_face::left, negative_z_direction}}, 
                {{0, 1, 0}, {block_face::bottom, positive_x_direction}});

    verify_step({{3, 1, 3}, {block_face::right, positive_z_direction}}, 
                {{3, 1, 3}, {block_face::top, negative_x_direction}});

    verify_step({{3, 1, 0}, {block_face::right, negative_z_direction}}, 
                {{3, 1, 0}, {block_face::bottom, negative_x_direction}});
}

TEST_THAT(Territory,
     WHAT(ComputeStep),
     WHEN(GivenAPositionOnTheEdgeOfASurfaceAndADirectionThatLeadsToATurnBlock),
     THEN(ReturnsAPositionOnTheAppropriateSurfaceOfThatBlock))
{
    create_cube_with_vertex_on_origin(4);

    this->t.add_block({{1, -1, 2}, "texture.jpg"});

    verify_step({{1, 0, 3}, {block_face::front, negative_z_direction}}, 
                {{1, -1, 2}, {block_face::top, negative_y_direction}});

    this->t.add_block({{4, 3, 2}, "texture.jpg"});

    verify_step({{3, 2, 2}, {block_face::right, positive_y_direction}}, 
                {{4, 3, 2}, {block_face::front, positive_x_direction}});

    this->t.add_block({{2, 4, 4}, "texture.jpg"});

    verify_step({{2, 3, 3}, {block_face::top, positive_y_direction}}, 
                {{2, 4, 4}, {block_face::front, positive_z_direction}});
}

} }
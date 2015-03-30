#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/canonical_direction.hpp"
#include "snake_overflow/dynamics.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/terrain.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Contains;
using ::testing::Eq;
using ::testing::Not;
using ::testing::Test;

class Terrain : public Test
{

protected:

    void create_cube_with_vertex_on_origin(int const side_length)
    {
        auto builder = terrain_builder{this->t};

        builder.add_cube({0, 0, 0}, 
                         side_length, 
                         "texture.jpg", 
                         {0, 0, 0, 255}, 
                         true);
    }

    void verify_step(util::value_ref<dynamics> d,
                     util::value_ref<dynamics> expected_result)
    {
        EXPECT_THAT(this->t.compute_step(d), Eq(expected_result));
    }

    block add_block_to_terrain(util::value_ref<point> p)
    {
        auto const b = block{p, "texture.jpg", {0, 0, 0, 255}, true};

        this->t.add_block(b);

        return b;
    }

    block add_non_solid_block_to_terrain(util::value_ref<point> p)
    {
        auto const b = block{p, "texture.jpg", {0, 0, 0, 255}, false};

        this->t.add_block(b);

        return b;
    }

protected:

    terrain t;

};

auto const positive_x_direction = canonical_direction::positive_x();
auto const negative_x_direction = canonical_direction::negative_x();
auto const positive_y_direction = canonical_direction::positive_y();
auto const negative_y_direction = canonical_direction::negative_y();
auto const positive_z_direction = canonical_direction::positive_z();
auto const negative_z_direction = canonical_direction::negative_z();

TEST_THAT(Terrain,
     WHAT(GetBlocks),
     WHEN(ImmediatelyAfterDefaultConstruction),
     THEN(ReturnsAnEmptyCollectionOfBlocks))
{
    auto const blocks = this->t.get_blocks();

    EXPECT_TRUE(blocks.empty());
}

TEST_THAT(Terrain,
     WHAT(AddBlock),
     WHEN(GivenABlockThatIsNotAlreadyPartOfTheTerrain),
     THEN(AddsTheBlockToTheTerrain))
{
    auto const b = add_block_to_terrain({0, 1, 2});

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));

    EXPECT_THAT(blocks[0], Eq(b));
}

TEST_THAT(Terrain,
     WHAT(AddBlock),
     WHEN(GivenABlockThatIsAlreadyPartOfTheTerrain),
     THEN(DoesNotAddThatBlockAgain))
{
    auto const b = add_block_to_terrain({0, 1, 2});

    this->t.add_block(b);

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));
}

TEST_THAT(Terrain,
     WHAT(RemoveBlock),
     WHEN(GivenABlockThatIsPartOfTheTerrain),
     WHEN(RemovesThatBlockFromTheTerrain))
{
    auto const b1 = add_block_to_terrain({0, 1, 2});
    auto const b2 = add_block_to_terrain({1, 2, 3});

    this->t.remove_block(b1.origin);

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));
    EXPECT_THAT(blocks, Not(Contains(b1)));
}

TEST_THAT(Terrain,
     WHAT(RemoveBlock),
     WHEN(GivenABlockThatIsNotPartOfTheTerrain),
     WHEN(DoesNothing))
{
    auto const b1 = add_block_to_terrain({0, 1, 2});
    auto const b2 = add_block_to_terrain({1, 2, 3});

    this->t.remove_block(b1.origin);

    this->t.remove_block(b1.origin);

    auto const blocks = this->t.get_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));
    EXPECT_THAT(blocks, Not(Contains(b1)));
}

TEST_THAT(Terrain,
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

TEST_THAT(Terrain,
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

TEST_THAT(Terrain,
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

TEST_THAT(Terrain,
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

TEST_THAT(Terrain,
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

TEST_THAT(Terrain,
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

TEST_THAT(Terrain,
     WHAT(ComputeStep),
     WHEN(GivenAPositionOnTheEdgeOfASurfaceAndADirectionThatLeadsToATurnBlock),
     THEN(ReturnsAPositionOnTheAppropriateSurfaceOfThatBlock))
{
    create_cube_with_vertex_on_origin(4);

    add_block_to_terrain({1, -1, 2});

    verify_step({{1, 0, 3}, {block_face::front, negative_z_direction}}, 
                {{1, -1, 2}, {block_face::top, negative_y_direction}});

    add_block_to_terrain({4, 3, 2});

    verify_step({{3, 2, 2}, {block_face::right, positive_y_direction}}, 
                {{4, 3, 2}, {block_face::front, positive_x_direction}});

    add_block_to_terrain({2, 4, 4});

    verify_step({{2, 3, 3}, {block_face::top, positive_y_direction}}, 
                {{2, 4, 4}, {block_face::front, positive_z_direction}});
}

TEST_THAT(Terrain,
     WHAT(ComputeStep),
     WHEN(WhenTheNextBlockToBeWalkedIsNotSolid),
     THEN(ThatBlockIsNotTakenIntoConsideration))
{
    create_cube_with_vertex_on_origin(4);

    add_non_solid_block_to_terrain({0, 0, 4});

    verify_step({{0, 0, 3}, {block_face::front, positive_z_direction}}, 
                {{0, 0, 3}, {block_face::top, positive_y_direction}});
}

} }
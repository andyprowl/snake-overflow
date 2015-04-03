#include "stdafx.hpp"

#include "snake_overflow/block.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/canonical_direction.hpp"
#include "snake_overflow/footprint.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/testing/fake_item.hpp"
#include <memory>

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

    void verify_step(util::value_ref<footprint> d,
                     util::value_ref<footprint> expected_result)
    {
        EXPECT_THAT(this->t.compute_next_footprint(d), Eq(expected_result));
    }

    block add_block_to_terrain(util::value_ref<point> p)
    {
        return add_solid_block_to_terrain(p);
    }

    block add_solid_block_to_terrain(util::value_ref<point> p)
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

    std::unique_ptr<item> make_item(util::value_ref<position> placement)
    {
        return std::make_unique<fake_item>(placement);
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
     WHAT(GetAllBlocks),
     WHEN(ImmediatelyAfterDefaultConstruction),
     THEN(ReturnsAnEmptyCollectionOfBlocks))
{
    auto const blocks = this->t.get_all_blocks();

    EXPECT_TRUE(blocks.empty());
}

TEST_THAT(Terrain,
     WHAT(AddBlock),
     WHEN(GivenABlockThatIsNotAlreadyPartOfTheTerrain),
     THEN(AddsTheBlockToTheTerrain))
{
    auto const b = add_block_to_terrain({0, 1, 2});

    auto const blocks = this->t.get_all_blocks();

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

    auto const blocks = this->t.get_all_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));
}

TEST_THAT(Terrain,
     WHAT(RemoveBlock),
     WHEN(GivenABlockThatIsPartOfTheTerrainAndContainsNoItems),
     WHEN(RemovesThatBlockFromTheTerrain))
{
    auto const b1 = add_block_to_terrain({0, 1, 2});
    auto const b2 = add_block_to_terrain({1, 2, 3});

    this->t.remove_block(b1.origin);

    auto const blocks = this->t.get_all_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));
    EXPECT_THAT(blocks, Not(Contains(b1)));
}

TEST_THAT(Terrain,
     WHAT(RemoveBlock),
     WHEN(GivenABlockThatIsPartOfTheTerrainAndContainsAtLeastOneItem),
     WHEN(Throws))
{
    auto const b = add_block_to_terrain({0, 1, 2});

    auto i = make_item({b.origin, block_face::front});

    this->t.add_item(std::move(i));

    EXPECT_THROW(this->t.remove_block(b.origin), block_not_empty_exception);
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

    auto const blocks = this->t.get_all_blocks();

    ASSERT_THAT(blocks.size(), Eq(1u));
    EXPECT_THAT(blocks, Not(Contains(b1)));
}

TEST_THAT(Terrain,
     WHAT(GetBlock),
     WHEN(GivenTheOriginOfABlockThatIsPartOfTheTerrain),
     THEN(ReturnsThatBlock))
{
    auto const origin = point{0, 1, 2};

    auto const b = add_block_to_terrain(origin);

    EXPECT_THAT(this->t.get_block(origin), Eq(b));
}

TEST_THAT(Terrain,
     WHAT(GetBlock),
     WHEN(GivenTheOriginOfABlockThatIsNotPartOfTheTerrain),
     THEN(Throws))
{
    EXPECT_THROW(this->t.get_block({0, 1, 2}), block_not_found_exception);
}

TEST_THAT(Terrain, 
     WHAT(ContainsBlock),
     WHEN(GivenAPointWhichIsTheOriginOfABlockThatIsPartOfTheTerrain),
     THEN(ReturnsTrue))
{
    auto const origin = point{0, 1, 2};

    add_block_to_terrain(origin);

    EXPECT_TRUE(this->t.contains_block(origin));
}

TEST_THAT(Terrain, 
     WHAT(ContainsBlock),
     WHEN(GivenAPointWhichIsNotTheOriginOfABlockThatIsPartOfTheTerrain),
     THEN(ReturnsFalse))
{
    EXPECT_FALSE(this->t.contains_block({0, 0, 0}));
}

TEST_THAT(Terrain, 
     WHAT(ContainsSolidBlock),
     WHEN(GivenAPointWhichIsTheOriginOfASolidBlockThatIsPartOfTheTerrain),
     THEN(ReturnsTrue))
{
    auto const origin = point{0, 1, 2};

    add_solid_block_to_terrain(origin);

    EXPECT_TRUE(this->t.contains_solid_block(origin));
}

TEST_THAT(Terrain, 
     WHAT(ContainsBlock),
     WHEN(GivenAPointWhichIsTheOriginOfANonSolidBlockThatIsPartOfTheTerrain),
     THEN(ReturnsFalse))
{
    auto const origin = point{0, 1, 2};

    add_non_solid_block_to_terrain(origin);

    EXPECT_FALSE(this->t.contains_solid_block(origin));
}

TEST_THAT(Terrain,
     WHAT(ForEachBlock),
     WHEN(GivenACallableObjectThatAcceptsABlock),
     THEN(InvokesThatCallableObjectForEachBlockInTheTerrain))
{
    create_cube_with_vertex_on_origin(3);

    auto blocks = std::vector<block>{};

    this->t.for_each_block([&blocks] (util::value_ref<block> b)
    {
        blocks.push_back(b);
    });

    EXPECT_THAT(blocks, Eq(this->t.get_all_blocks()));
}

TEST_THAT(Terrain, 
     WHAT(ContainsBlock),
     WHEN(GivenAPointWhichIsNotTheOriginOfAnyBlockThatIsPartOfTheTerrain),
     THEN(ReturnsFalse))
{
    EXPECT_FALSE(this->t.contains_solid_block({0, 0, 0}));
}

TEST_THAT(Terrain,
     WHAT(AddItem),
     WHEN(GivenAnItemWithAValidPosition),
     THEN(AcquiresItsOwnershipAndPlacesTheItem))
{
    create_cube_with_vertex_on_origin(4);

    auto const pos = position{{1, 0, 1}, block_face::front};

    auto i = make_item(pos);

    auto added_item = i.get();

    this->t.add_item(std::move(i));

    auto const b = this->t.get_block(pos.location);

    EXPECT_THAT(b.items.size(), Eq(1u));

    EXPECT_THAT(b.items, Contains(added_item));
}

TEST_THAT(Terrain,
     WHAT(AddItem),
     WHEN(GivenAnItemWithAPositionThatDoesNotBelongToAnyExistingBlock),
     THEN(Throws))
{
    create_cube_with_vertex_on_origin(4);

    auto const bogus_position = position{{10, 15, 1}, block_face::front};

    auto i = make_item(bogus_position);

    EXPECT_THROW(this->t.add_item(std::move(i)), block_not_found_exception);
}

TEST_THAT(Terrain,
     WHAT(AddItem),
     WHEN(GivenAnItemWithAPositionThatBelongsToAnExistingBlockButIsNotWalkable),
     THEN(Throws))
{
    create_cube_with_vertex_on_origin(4);

    auto const bad_position = position{{0, 0, 0}, block_face::back};

    auto i = make_item(bad_position);

    EXPECT_THROW(this->t.add_item(std::move(i)), bad_item_position_exception);
}

TEST_THAT(Terrain,
     WHAT(AddItem),
     WHEN(GivenAnItemWithAValidPositionInWhichAnotherItemIsAlreadyPresent),
     THEN(Throws))
{
    create_cube_with_vertex_on_origin(4);

    auto const pos = position{{1, 0, 1}, block_face::front};

    auto i1 = make_item(pos);

    this->t.add_item(std::move(i1));

    auto i2 = make_item(pos);

    EXPECT_THROW(this->t.add_item(std::move(i2)), bad_item_position_exception);
}

TEST_THAT(Terrain,
     WHAT(RemoveItem),
     WHEN(GivenAnItemThatWasPreviouslyAddedToTheTerrain),
     THEN(RemovesThatItemFromTheBlockItIsPlacedOnAndReturnsItsOwnership))
{
    create_cube_with_vertex_on_origin(4);

    auto const pos = position{{1, 0, 1}, block_face::front};

    auto i = make_item(pos);

    auto& added_item = *i;

    this->t.add_item(std::move(i));

    auto removed_item = this->t.remove_item(added_item);

    EXPECT_THAT(removed_item.get(), Eq(&added_item));

    auto const b = this->t.get_block(pos.location);

    EXPECT_TRUE(b.items.empty());
}

TEST_THAT(Terrain,
     WHAT(RemoveItem),
     WHEN(GivenAnItemThatWasNotPreviouslyAddedToTheTerrain),
     THEN(Throws))
{
    create_cube_with_vertex_on_origin(4);

    auto const pos = position{{1, 0, 1}, block_face::front};

    auto i = make_item(pos);

    EXPECT_THROW(this->t.remove_item(*i), item_not_found_exception);
}

TEST_THAT(Terrain,
     WHAT(GetNumOfItems),
     WHEN(Always),
     THEN(ReturnsTheNumberOfItemsPresentInTheTerrain))
{
    create_cube_with_vertex_on_origin(4);

    EXPECT_THAT(this->t.get_num_of_items(), Eq(0));

    this->t.add_item(make_item({{1, 0, 1}, block_face::front}));

    EXPECT_THAT(this->t.get_num_of_items(), Eq(1));

    auto i = make_item({{1, 0, 2}, block_face::front});

    auto& last_added_item = *i;

    this->t.add_item(std::move(i));

    EXPECT_THAT(this->t.get_num_of_items(), Eq(2));

    this->t.remove_item(last_added_item);

    EXPECT_THAT(this->t.get_num_of_items(), Eq(1));
}


TEST_THAT(Terrain,
     WHAT(ForEachItem),
     WHEN(GivenACallableObjectThatAcceptsAItem),
     THEN(InvokesThatCallableObjectForEachItemInTheTerrain))
{
    create_cube_with_vertex_on_origin(3);

    auto i1 = make_item({{1, 0, 2}, block_face::front});
    auto i1_ptr = i1.get();
    this->t.add_item(std::move(i1));

    auto i2 = make_item({{0, 1, 2}, block_face::top});
    auto i2_ptr = i2.get();
    this->t.add_item(std::move(i2));

    auto i3 = make_item({{0, 1, 1}, block_face::left});
    auto i3_ptr = i3.get();
    this->t.add_item(std::move(i3));

    auto items = std::vector<item const*>{};

    this->t.for_each_item([&items] (util::value_ref<item> i)
    {
        items.push_back(&i);
    });

    EXPECT_THAT(items.size(), Eq(3u));

    EXPECT_THAT(items, Contains(i1_ptr));
    EXPECT_THAT(items, Contains(i2_ptr));
    EXPECT_THAT(items, Contains(i3_ptr));
}

TEST_THAT(Terrain,
     WHAT(IsPositionFreeOfItems),
     WHEN(GivenAPositionAndATerrainThatContainsAnItemAtThatPosition),
     THEN(ReturnsFalse))
{
    create_cube_with_vertex_on_origin(4);

    auto const pos = position{{1, 0, 1}, block_face::front};

    this->t.add_item(make_item(pos));

    EXPECT_FALSE(is_position_free_of_items(pos, this->t));
}

TEST_THAT(Terrain,
     WHAT(IsPositionFreeOfItems),
     WHEN(GivenAPositionAndATerrainThatDoesNotContainAnItemAtThatPosition),
     THEN(ReturnsTrue))
{
    create_cube_with_vertex_on_origin(4);

    auto const pos = position{{1, 0, 1}, block_face::front};

    EXPECT_TRUE(is_position_free_of_items(pos, this->t));
}

TEST_THAT(Terrain,
     WHAT(IsPositionWalkable),
     WHEN(GivenAPositionAndATerrainWhereThePositionDoesNotHaveAnAdjacentBlock),
     THEN(ReturnsTrue))
{
    create_cube_with_vertex_on_origin(4);
    
    EXPECT_TRUE(is_position_walkable({{1, 0, 1}, block_face::front}, this->t));
    EXPECT_TRUE(is_position_walkable({{1, 3, 1}, block_face::back}, this->t));
    EXPECT_TRUE(is_position_walkable({{0, 0, 1}, block_face::left}, this->t));
    EXPECT_TRUE(is_position_walkable({{3, 0, 1}, block_face::right}, this->t));
    EXPECT_TRUE(is_position_walkable({{1, 0, 3}, block_face::top}, this->t));
    EXPECT_TRUE(is_position_walkable({{1, 1, 0}, block_face::bottom}, this->t));
}

TEST_THAT(Terrain,
     WHAT(IsPositionWalkable),
     WHEN(GivenAPositionAndATerrainWhereThePositionHasAnAdjacentSolidBlock),
     THEN(ReturnsFalse))
{
    create_cube_with_vertex_on_origin(4);
    
    EXPECT_FALSE(is_position_walkable({{1, 1, 1}, block_face::front}, this->t));
    EXPECT_FALSE(is_position_walkable({{1, 2, 1}, block_face::back}, this->t));
    EXPECT_FALSE(is_position_walkable({{1, 0, 1}, block_face::left}, this->t));
    EXPECT_FALSE(is_position_walkable({{2, 0, 1}, block_face::right}, this->t));
    EXPECT_FALSE(is_position_walkable({{1, 0, 2}, block_face::top}, this->t));
    EXPECT_FALSE(is_position_walkable({{1, 1, 1}, block_face::bottom}, 
                                      this->t));
}

TEST_THAT(Terrain,
     WHAT(IsPositionWalkable),
     WHEN(GivenAPositionAndATerrainWhereThePositionHasAnAdjacentNonSolidBlock),
     THEN(ReturnsTrue))
{
    create_cube_with_vertex_on_origin(4);

    auto builder = terrain_builder{this->t};

    builder.add_cube({0, 0, 4}, 3, "", {0, 0, 0, 255}, false);
    
    EXPECT_TRUE(is_position_walkable({{1, 1, 3}, block_face::top}, this->t));
}

TEST_THAT(Terrain,
     WHAT(IsPositionWalkable),
     WHEN(GivenAPositionWhichIsNotOnASolidBlock),
     THEN(ReturnsFalse))
{
    create_cube_with_vertex_on_origin(4);

    auto builder = terrain_builder{this->t};

    builder.add_cube({0, 0, 4}, 3, "", {0, 0, 0, 255}, false);
    
    EXPECT_FALSE(is_position_walkable({{1, 1, 6}, block_face::top}, this->t));
}

TEST_THAT(Terrain,
     WHAT(CanPlaceItemAtPosition),
     WHEN(GivenAPositionThatIsWalkableAndFreeOfItems),
     THEN(ReturnsTrue))
{
    create_cube_with_vertex_on_origin(4);

    auto const pos = position{{1, 0, 1}, block_face::front};

    EXPECT_TRUE(can_place_item_at_position(pos, this->t));
}

TEST_THAT(Terrain,
     WHAT(CanPlaceItemAtPosition),
     WHEN(GivenAPositionThatIsWalkableButNotFreeOfItems),
     THEN(ReturnsFalse))
{
    create_cube_with_vertex_on_origin(4);

    auto const pos = position{{1, 0, 1}, block_face::front};

    auto i = make_item(pos);

    this->t.add_item(std::move(i));

    EXPECT_FALSE(can_place_item_at_position(pos, this->t));
}

TEST_THAT(Terrain,
     WHAT(CanPlaceItemAtPosition),
     WHEN(GivenAPositionThatIsFreeOfItemsButNotWalkable),
     THEN(ReturnsFalse))
{
    create_cube_with_vertex_on_origin(4);

    auto const pos = position{{1, 0, 1}, block_face::right};
    
    EXPECT_FALSE(can_place_item_at_position(pos, this->t));
}

TEST_THAT(Terrain,
     WHAT(GetAllFreeValidItemPositions),
     WHEN(Always),
     THEN(ReturnsOnlyPositionsOnTheNonNeighboringSurfaceOfABlock))
{
    create_cube_with_vertex_on_origin(2);

    auto const positions = this->t.get_all_free_item_positions();

    EXPECT_THAT(positions.size(), Eq(24));

    EXPECT_THAT(positions, Contains(position{{0, 0, 0}, block_face::front}));    
    EXPECT_THAT(positions, Contains(position{{0, 0, 1}, block_face::front}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 0}, block_face::front}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 1}, block_face::front}));    

    EXPECT_THAT(positions, Contains(position{{0, 1, 0}, block_face::back}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 1}, block_face::back}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 0}, block_face::back}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 1}, block_face::back}));    

    EXPECT_THAT(positions, Contains(position{{0, 0, 0}, block_face::left}));    
    EXPECT_THAT(positions, Contains(position{{0, 0, 1}, block_face::left}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 0}, block_face::left}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 1}, block_face::left}));    

    EXPECT_THAT(positions, Contains(position{{1, 0, 0}, block_face::right}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 1}, block_face::right}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 0}, block_face::right}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 1}, block_face::right}));    

    EXPECT_THAT(positions, Contains(position{{0, 0, 1}, block_face::top}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 1}, block_face::top}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 1}, block_face::top}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 1}, block_face::top}));    

    EXPECT_THAT(positions, Contains(position{{0, 0, 0}, block_face::bottom}));    
    EXPECT_THAT(positions, Contains(position{{0, 1, 0}, block_face::bottom}));    
    EXPECT_THAT(positions, Contains(position{{1, 0, 0}, block_face::bottom}));    
    EXPECT_THAT(positions, Contains(position{{1, 1, 0}, block_face::bottom}));    
}

TEST_THAT(Terrain,
     WHAT(GetAllFreeValidItemPositions),
     WHEN(Always),
     THEN(ReturnsOnlyPositionsThatAreNotOccupiedByAnyItem))
{
    create_cube_with_vertex_on_origin(2);

    auto const pos1 = position{{0, 0, 0}, block_face::front};

    this->t.add_item(make_item(pos1));

    auto const pos2 = position{{0, 0, 1}, block_face::front};

    this->t.add_item(make_item(pos2));

    auto const positions = this->t.get_all_free_item_positions();

    EXPECT_THAT(positions.size(), Eq(22));

    EXPECT_THAT(positions, Not(Contains(pos1)));
    EXPECT_THAT(positions, Not(Contains(pos2)));
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
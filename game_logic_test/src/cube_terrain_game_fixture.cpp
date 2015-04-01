#include "stdafx.hpp"

#include "snake_overflow/testing/cube_terrain_game_fixture.hpp"

namespace snake_overflow { namespace testing
{

void CubeTerrainGameFixture::SetUp()
{
    auto t = create_terrain();

    auto s = create_snake(*t);

    this->g = std::make_unique<game>(std::move(t), std::move(s));
}

std::unique_ptr<terrain> CubeTerrainGameFixture::create_terrain()
{
    auto t = std::make_unique<terrain>();

    this->habitat = t.get();

    auto builder = terrain_builder{*t};

    builder.add_cube(point::zero(), 
                     this->terrain_side_length, 
                     "", 
                     rgba_color::white(), 
                     true);

    return t;
}

std::unique_ptr<snake> CubeTerrainGameFixture::create_snake(terrain& habitat)
{
    auto const initial_snake_footprint = footprint{
        point::zero(), 
        {block_face::front, canonical_direction::positive_z()}};

    this->initial_snake_length = 3;

    auto s = std::make_unique<snake>(habitat, 
                                     initial_snake_footprint,
                                     this->initial_snake_length);

    this->hero = s.get();

    return s;
}

game& CubeTerrainGameFixture::get_game() const
{
    return *(this->g);
}

terrain& CubeTerrainGameFixture::get_terrain() const
{
    return *(this->habitat);
}

snake& CubeTerrainGameFixture::get_snake() const
{
    return *(this->hero);
}

} }
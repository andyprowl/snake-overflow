#include "stdafx.hpp"

#include "snake_overflow/testing/game_fixture.hpp"

namespace snake_overflow { namespace testing
{

void GameFixture::SetUp()
{
    auto t = create_terrain();

    auto s = create_snake(*t);

    this->g = std::make_unique<game>(std::move(t), std::move(s));
}

std::unique_ptr<terrain> GameFixture::create_terrain()
{
    auto t = std::make_unique<terrain>();

    this->habitat = t.get();

    auto builder = terrain_builder{*t};

    builder.add_cube(point::zero(), 4, "", rgba_color::white(), true);

    return t;
}

std::unique_ptr<snake> GameFixture::create_snake(terrain& habitat)
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

game& GameFixture::get_game() const
{
    return *(this->g);
}

terrain& GameFixture::get_terrain() const
{
    return *(this->habitat);
}

snake& GameFixture::get_snake() const
{
    return *(this->hero);
}

} }
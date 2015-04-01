#pragma once

#include "snake_overflow/game.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"

namespace snake_overflow { namespace testing
{

class CubeTerrainGameFixture : public ::testing::Test
{

protected:

    virtual void SetUp() override;

    std::unique_ptr<terrain> create_terrain();

    std::unique_ptr<snake> create_snake(terrain& habitat);

    game& get_game() const;

    terrain& get_terrain() const;

    snake& get_snake() const;

protected:

    terrain* habitat = nullptr;

    snake* hero = nullptr;

    int initial_snake_length = 3;

    int terrain_side_length = 7;

    std::unique_ptr<game> g;

};

} }
#pragma once

#include "snake_overflow/game.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/testing/item_spawner_spy.hpp"
#include "snake_overflow/testing/terrain_item_filler_spy.hpp"

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

    snake_body& get_snake_body() const;

protected:

    terrain* habitat = nullptr;

    snake* hero = nullptr;

    snake_body* hero_body = nullptr;

    int initial_snake_length = 3;

    int terrain_side_length = 7;

    std::string snake_skin = "SKIN";

    std::unique_ptr<item_spawner_spy> spawner;

    terrain_item_filler_spy* terrain_filler = nullptr;

    std::unique_ptr<game> g;

};

} }
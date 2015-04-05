#pragma once

#include "snake_overflow/terrain.hpp"
#include <memory>

namespace snake_overflow
{

class game_map
{

public:

    game_map(std::string name, std::unique_ptr<terrain>&& ground);

    std::unique_ptr<game_map> clone() const;

    std::string get_name() const;

    terrain& get_terrain() const;

private:

    std::string name;

    std::unique_ptr<terrain> ground;

};

}
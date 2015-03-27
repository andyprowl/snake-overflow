#pragma once

namespace snake_overflow { namespace game_logic
{

class territory;

class cube_builder
{

public:

    cube_builder(territory& build_site);

private:

    territory& build_site;

};

} }
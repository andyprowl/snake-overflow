#include "stdafx.hpp"

#include "snake_overflow/game.hpp"

namespace snake_overflow
{

game::game(std::unique_ptr<game_map>&& habitat, 
           std::unique_ptr<snake>&& hero,
           std::unique_ptr<terrain_item_filler>&& habitat_filler)
    : is_game_over{false, hero->is_dead}
    , is_game_paused{false, is_game_over}
    , score{0, is_game_over, 0, boost::none}
    , terrain_filling_interval{100, is_game_over, 1, boost::none}
    , habitat{std::move(habitat)}
    , hero{std::move(hero)}
    , habitat_filler{std::move(habitat_filler)}
    , age{0}
{
}

game_map& game::get_map() const
{
    return *(this->habitat);
}

terrain& game::get_terrain() const
{
    return this->habitat->get_terrain();
}

snake& game::get_snake() const
{
    return *(this->hero);
}

void game::update()
{
    if (this->is_game_paused || this->is_game_over)
    {
        return;
    }

    this->hero->update();

    fill_terrain_if_due_time();

    make_all_items_age();

    ++(this->age);
}

void game::throw_if_game_is_over() const
{
    if (this->is_game_over)
    {
        throw game_over_exception{};
    }
}

void game::fill_terrain_if_due_time() const
{
    if (this->age % this->terrain_filling_interval == 0)
    {
        this->habitat_filler->fill_terrain();
    }
}

void game::make_all_items_age() const
{
    auto items = std::vector<item*>{};

    auto& t = get_terrain();

    items.reserve(t.get_num_of_items());

    t.for_each_item([&items] (item& i)
    {
        items.push_back(&i);
    });

    for (auto const i : items) { i->age(); }
}

void toggle_game_pause(game& g)
{
    g.is_game_paused = !(g.is_game_paused);
}

}
#include "stdafx.hpp"

#include "snake_overflow/item_position_picker.hpp"
#include "snake_overflow/probabilistic_item_spawner.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/terrain.hpp"
#include <cassert>
#include <numeric>

namespace snake_overflow
{
    
probabilistic_item_spawner::probabilistic_item_spawner(
    terrain& ground, 
    std::unique_ptr<item_position_picker>&& position_picker)
    : item_spawner{ground}
    , position_picker{std::move(position_picker)}
{
}

void probabilistic_item_spawner::spawn(int const num_of_items_to_spawn)
{
    throw_if_probabilities_do_not_sum_up_to_one_hundred();

    auto num_of_spawned_items = 0;
    while (num_of_spawned_items < num_of_items_to_spawn)
    {
        try
        {
            spawn_new_item();

            ++num_of_spawned_items;
        }
        catch (std::exception const&)
        {
        }
    }
}

void probabilistic_item_spawner::register_item_factory(item_factory f, 
                                                       int const probability)
{
    auto const sum = get_sum_of_registered_factory_probabilities();
    if (sum + probability > 100)
    {
        throw bad_factory_probability_distribution_exception{};
    }

    this->factories.push_back(std::move(f));
    
    this->factory_weights.push_back(probability);
}

void probabilistic_item_spawner::
    throw_if_probabilities_do_not_sum_up_to_one_hundred() const
{
    if (get_sum_of_registered_factory_probabilities() != 100)
    {
        throw bad_factory_probability_distribution_exception{};
    }
}

int probabilistic_item_spawner::
    get_sum_of_registered_factory_probabilities() const
{
    return std::accumulate(std::begin(this->factory_weights),
                           std::end(this->factory_weights),
                           0,
                           std::plus<int>{});
}

void probabilistic_item_spawner::spawn_new_item() const
{
    auto const pos = this->position_picker->pick_item_position();

    auto const index = pick_random_factory_index();

    assert(index < this->factories.size());

    auto const& f = this->factories[index];

    auto i = f(pos);

    this->ground.add_item(std::move(i));
}

int probabilistic_item_spawner::pick_random_factory_index() const
{
    return this->index_generator.generate_in_weighed_range(
        this->factory_weights);
}

}
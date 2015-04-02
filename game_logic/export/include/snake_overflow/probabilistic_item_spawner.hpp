#pragma once

#include "snake_overflow/item_spawner.hpp"
#include "snake_overflow/random_integer_generator.hpp"
#include "util/value_ref.hpp"
#include <functional>
#include <memory>

namespace snake_overflow
{

struct position;

class item;
class item_position_picker;
class terrain;

class bad_factory_probability_distribution_exception 
    : public virtual std::exception
{
};

class probabilistic_item_spawner : public item_spawner
{

public:

    using item_factory = 
          std::function<std::unique_ptr<item>(util::value_ref<position>)>;

public:

    probabilistic_item_spawner(
        terrain& ground, 
        std::unique_ptr<item_position_picker>&& position_picker);
    
    virtual void spawn(int num_of_items_to_spawn) override;

    void register_item_factory(item_factory f, int probability);

private:

    void throw_if_probabilities_do_not_sum_up_to_one_hundred() const;

    int get_sum_of_registered_factory_probabilities() const;

    void spawn_new_item() const;

    int pick_random_factory_index() const;

private:

    std::unique_ptr<item_position_picker> position_picker;

    std::vector<item_factory> factories;

    std::vector<int> factory_weights;

    random_integer_generator index_generator;

};

}
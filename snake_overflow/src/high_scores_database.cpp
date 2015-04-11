#include "stdafx.hpp"

#include "snake_overflow/high_scores_database.hpp"

namespace snake_overflow
{
    
high_scores_database::high_scores_database()
{
}

high_scores_rankings& high_scores_database::get_rankings_for_map(
    util::value_ref<std::string> map_name) const
{
    auto const it = this->scores_map.find(map_name);
    if (it == std::cend(this->scores_map))
    {
        auto const path = get_high_scores_folder() / map_name;

        this->scores_map.emplace(std::piecewise_construct,
                                 std::forward_as_tuple(map_name), 
                                 std::forward_as_tuple(std::move(path)));
    }

    return scores_map.at(map_name);
}

boost::filesystem::path high_scores_database::get_high_scores_folder() const
{
    if (boost::filesystem::is_directory("../../high scores"))
    {
        return {"../../high scores"};
    }
    else
    {
        return boost::filesystem::current_path() / "high scores";
    }
}

}
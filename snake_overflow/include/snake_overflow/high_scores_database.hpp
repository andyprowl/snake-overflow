#pragma once

#include "snake_overflow/persisted_high_scores_rankings.hpp"
#include <boost/filesystem.hpp>
#include <unordered_map>

namespace snake_overflow
{
    
class high_scores_database
{
    
public:

    high_scores_database();
    
    high_scores_rankings& get_rankings_for_map(
        util::value_ref<std::string> map_name) const;

private:

    using high_scores_map = 
          std::unordered_map<std::string, persisted_high_scores_rankings>;

private:

    boost::filesystem::path get_high_scores_folder() const;

private:
    
    mutable high_scores_map scores_map;

};

}
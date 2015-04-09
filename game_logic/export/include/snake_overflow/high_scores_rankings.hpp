#pragma once

#include "snake_overflow/score_record.hpp"
#include <functional>
#include <set>

namespace snake_overflow
{
    
class high_scores_rankings
{

public:

    void add_score(score_record s);

    std::vector<score_record> get_rankings() const;

    std::vector<score_record> get_top_scores(int num_of_scores) const;

private:
    
    std::set<score_record, std::greater<>> rankings;

};

}
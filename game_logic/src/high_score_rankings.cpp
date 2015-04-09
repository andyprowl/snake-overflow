#include "stdafx.hpp"

#include "snake_overflow/high_scores_rankings.hpp"
#include <iterator>

namespace snake_overflow
{

void high_scores_rankings::add_score(score_record s)
{
    rankings.insert(std::move(s));
}

std::vector<score_record> high_scores_rankings::get_rankings() const
{
    return {std::cbegin(rankings), std::cend(rankings)};
}

std::vector<score_record> high_scores_rankings::get_top_scores(
    int const num_of_scores) const
{
    return {std::cbegin(rankings), 
            std::next(std::cbegin(rankings), num_of_scores)};
}

}
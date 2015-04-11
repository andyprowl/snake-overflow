#include "stdafx.hpp"

#include "snake_overflow/volatile_high_scores_rankings.hpp"
#include <algorithm>
#include <iterator>

namespace snake_overflow
{

void volatile_high_scores_rankings::add_score(score_record s)
{
    this->rankings.insert(std::move(s));
}

std::vector<score_record> volatile_high_scores_rankings::get_rankings() const
{
    return {std::cbegin(this->rankings), std::cend(this->rankings)};
}

std::vector<score_record> volatile_high_scores_rankings::get_top_scores(
    int const num_of_scores) const
{
    auto const total_scores = static_cast<int>(this->rankings.size());

    auto const top_scores = std::min(num_of_scores, total_scores);

    return {std::cbegin(this->rankings), 
            std::next(std::cbegin(this->rankings), top_scores)};
}

void volatile_high_scores_rankings::clear()
{
    this->rankings.clear();
}

}
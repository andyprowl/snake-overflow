#pragma once

#include "snake_overflow/score_record.hpp"

namespace snake_overflow
{

class high_scores_rankings
{

public:

    virtual ~high_scores_rankings() = default;

    virtual void add_score(score_record s) = 0;

    virtual std::vector<score_record> get_rankings() const = 0;

    virtual std::vector<score_record> get_top_scores(
        int num_of_scores) const = 0;

    virtual void clear() = 0;

};

}
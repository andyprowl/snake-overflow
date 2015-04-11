#pragma once

#include "snake_overflow/high_scores_rankings.hpp"
#include <functional>
#include <set>

namespace snake_overflow
{
    
class volatile_high_scores_rankings : public high_scores_rankings
{

public:

    virtual void add_score(score_record s) override;

    virtual std::vector<score_record> get_rankings() const override;

    virtual std::vector<score_record> get_top_scores(
        int num_of_scores) const override;

    virtual void clear() override;

private:
    
    std::set<score_record, std::greater<>> rankings;

};

}
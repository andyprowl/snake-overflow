#pragma once

#include "snake_overflow/volatile_high_scores_rankings.hpp"
#include "snake_overflow/high_scores_stream_persister.hpp"
#include <boost/filesystem.hpp>

namespace snake_overflow
{

class persisted_high_scores_rankings : public high_scores_rankings
{

public:

    persisted_high_scores_rankings(boost::filesystem::path scores_file);

    virtual void add_score(score_record s) override;

    virtual std::vector<score_record> get_rankings() const override;

    virtual std::vector<score_record> get_top_scores(
        int num_of_scores,
        int starting_rank = 0) const override;

    virtual void clear() override;

    virtual int get_length() const override;

private:

    boost::filesystem::path scores_file;

    volatile_high_scores_rankings rankings;

    std::unique_ptr<high_scores_stream_persister> persister;

};

}
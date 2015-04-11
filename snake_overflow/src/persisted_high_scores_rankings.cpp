#include "stdafx.hpp"

#include "snake_overflow/persisted_high_scores_rankings.hpp"
#include <fstream>

namespace snake_overflow
{

persisted_high_scores_rankings::persisted_high_scores_rankings(
    boost::filesystem::path scores_file)
    : scores_file{std::move(scores_file)}
{
    this->persister = 
        std::make_unique<high_scores_stream_persister>(this->rankings);

    auto fs = std::ifstream{this->scores_file.c_str()}; 
    if (fs)
    {
        this->persister->load(fs);
    }
}

void persisted_high_scores_rankings::add_score(score_record s)
{
    this->rankings.add_score(std::move(s));

    auto fs = std::ofstream{this->scores_file.c_str()};

    this->persister->store(fs);
}

std::vector<score_record> persisted_high_scores_rankings::get_rankings() const
{
    return this->rankings.get_rankings();
}

std::vector<score_record> persisted_high_scores_rankings::get_top_scores(
    int const num_of_scores) const
{
    return this->rankings.get_top_scores(num_of_scores);
}

void persisted_high_scores_rankings::clear()
{
    this->rankings.clear();

    auto fs = std::fstream{this->scores_file.c_str()};

    this->persister->store(fs);
}

}
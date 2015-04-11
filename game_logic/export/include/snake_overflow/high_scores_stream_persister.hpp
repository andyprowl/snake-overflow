#pragma once

#include "util/value_ref.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace snake_overflow
{

struct score_record;

class high_scores_rankings;

class high_scores_stream_persister
{

public:

    high_scores_stream_persister(high_scores_rankings& rankings);

    void store(std::ostream& os);

    void load(std::istream& is);

private:

    score_record parse_score_record(
        util::value_ref<std::vector<std::string>> tokens) const;

private:

    high_scores_rankings& rankings;

};

}
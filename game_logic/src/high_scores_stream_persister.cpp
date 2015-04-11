#include "stdafx.hpp"

#include "snake_overflow/high_scores_stream_persister.hpp"
#include "snake_overflow/high_scores_rankings.hpp"
#include "util/tokenize.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

namespace snake_overflow
{

std::ostream& operator << (std::ostream& os, util::value_ref<score_record> s)
{
    os << s.player_name << ";";
    
    os << s.points << ";";
    
    auto const time = s.date.time_since_epoch();

    os << std::chrono::duration_cast<std::chrono::seconds>(time).count();

    return os;
}

high_scores_stream_persister::high_scores_stream_persister(
    high_scores_rankings& rankings)
    : rankings{rankings}
{
}

void high_scores_stream_persister::store(std::ostream& os)
{
    auto const scores = this->rankings.get_rankings();
    for (auto const s : scores)
    {
        os << s << std::endl;
    }
}

void high_scores_stream_persister::load(std::istream& is)
{
    auto line = std::string{};
    while (std::getline(is, line))
    {
        auto const tokens = util::tokenize(line, ";");

        auto score = parse_score_record(tokens);

        this->rankings.add_score(std::move(score));
    }
}

score_record high_scores_stream_persister::parse_score_record(
    util::value_ref<std::vector<std::string>> tokens) const
{
    auto const player_name = tokens[0];

    auto const points = std::stoi(tokens[1]);

    auto const seconds_since_epoch = std::stoi(tokens[2]);

    auto const date = std::chrono::system_clock::time_point{
        std::chrono::seconds(seconds_since_epoch)};
    
    return {std::move(player_name), points, std::move(date)};
}

}
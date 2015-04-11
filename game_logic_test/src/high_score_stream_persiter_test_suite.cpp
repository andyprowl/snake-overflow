#include "stdafx.hpp"

#include "snake_overflow/high_scores_stream_persister.hpp"
#include "snake_overflow/high_scores_rankings.hpp"
#include "util/tokenize.hpp"
#include <sstream>

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class HighScoreStreamPersister : public Test
{

protected:

    void expect_equal_dates_with_second_precision(
        util::value_ref<std::chrono::system_clock::time_point> actual,
        util::value_ref<std::chrono::system_clock::time_point> expected)
    {
        auto const ad = std::chrono::duration_cast<std::chrono::seconds>(
            actual.time_since_epoch());

        auto const ed = std::chrono::duration_cast<std::chrono::seconds>(
            expected.time_since_epoch());

        EXPECT_THAT(ad.count(), Eq(ed.count()));
    }

protected:

    high_scores_rankings rankings;

    high_scores_stream_persister persister{rankings};

};

TEST_THAT(HighScoreStreamPersister,
     WHAT(Store),
     WHEN(GivenAHighScoreRanking),
     THEN(SerializesEachScoreOnAnIndividualLineIntoTheStream))
{
    auto const date1 = std::chrono::system_clock::now();
    auto const date2 = std::chrono::system_clock::now() + std::chrono::hours(1);
    auto const date3 = std::chrono::system_clock::now() - std::chrono::hours(1);

    this->rankings.add_score({"player1", 125, date1});
    this->rankings.add_score({"player2", 250, date2});
    this->rankings.add_score({"player3", 350, date3});

    auto ss = std::ostringstream{};
    this->persister.store(ss);

    auto serialized_rankings = ss.str();

    auto scores = util::tokenize(serialized_rankings, "\n");
    ASSERT_THAT(scores.size(), Eq(3u));
}

TEST_THAT(HighScoreStreamPersister,
     WHAT(Load),
     WHEN(GivenAStreamForTheSerializationOfTheHighScoresOfARanking),
     THEN(DeserializesThoseScoresAndAddsThemToTheAssociatedRanking))
{
    auto const date1 = std::chrono::system_clock::now();
    auto const date2 = std::chrono::system_clock::now() + std::chrono::hours(1);
    auto const date3 = std::chrono::system_clock::now() - std::chrono::hours(1);

    this->rankings.add_score({"player1", 125, date1});
    this->rankings.add_score({"player2", 250, date2});
    this->rankings.add_score({"player3", 350, date3});

    auto ss = std::stringstream{};
    this->persister.store(ss);

    this->rankings.clear();

    this->persister.load(ss);

    auto const all_scores = this->rankings.get_rankings();

    ASSERT_THAT(all_scores.size(), Eq(3u));

    EXPECT_THAT(all_scores[0].player_name, Eq("player3"));
    EXPECT_THAT(all_scores[0].points, Eq(350));
    expect_equal_dates_with_second_precision(all_scores[0].date, date3);

    EXPECT_THAT(all_scores[1].player_name, Eq("player2"));
    EXPECT_THAT(all_scores[1].points, Eq(250));
    expect_equal_dates_with_second_precision(all_scores[1].date, date2);

    EXPECT_THAT(all_scores[2].player_name, Eq("player1"));
    EXPECT_THAT(all_scores[2].points, Eq(125));
    expect_equal_dates_with_second_precision(all_scores[2].date, date1);
}

} }
#include "stdafx.hpp"

#include "snake_overflow/high_scores_rankings.hpp"

namespace snake_overflow { namespace testing
{

using ::testing::Eq;
using ::testing::Test;

class HighScoresRankings : public Test
{

protected:

    high_scores_rankings rankings;

};

TEST_THAT(HighScoresRankings,
     WHAT(GetAllScores),
     WHEN(ImmediatelyAfterConstruction),
     THEN(ReturnsAnEmptyRanking))
{
    auto const all_scores = this->rankings.get_rankings();

    EXPECT_TRUE(all_scores.empty());
}

TEST_THAT(HighScoresRankings,
     WHAT(AddScore),
     WHEN(GivenAScore),
     THEN(AddsItToTheRankings))
{
    auto s = score_record{"player1", 125, std::chrono::system_clock::now()};

    this->rankings.add_score(s);

    auto const all_scores = this->rankings.get_rankings();

    ASSERT_THAT(all_scores.size(), Eq(1u));

    EXPECT_THAT(all_scores[0], Eq(s));
}

TEST_THAT(HighScoresRankings,
     WHAT(GetAllScores),
     WHEN(AfterAFewScoresHaveBeenAdded),
     THEN(ReturnsTheScoresInDescendingRankingOrder))
{
    auto const now = std::chrono::system_clock::now();

    auto s1 = score_record{"p1", 1, now + std::chrono::hours(2)};    
    auto s2 = score_record{"p2", 5, now + std::chrono::hours(1)};
    auto s3 = score_record{"p3", 3, now + std::chrono::hours(3)};
    auto s4 = score_record{"p1", 3, now + std::chrono::hours(2)};

    this->rankings.add_score(s1);
    this->rankings.add_score(s2);
    this->rankings.add_score(s3);
    this->rankings.add_score(s4);

    auto const all_scores = this->rankings.get_rankings();

    ASSERT_THAT(all_scores.size(), Eq(4u));

    EXPECT_THAT(all_scores[0], Eq(s2));
    EXPECT_THAT(all_scores[1], Eq(s4));
    EXPECT_THAT(all_scores[2], Eq(s3));
    EXPECT_THAT(all_scores[3], Eq(s1));
}

TEST_THAT(HighScoresRankings,
     WHAT(GetTopScores),
     WHEN(GivenANumberOfScoresGreaterThanTheTotalNumberOfScores),
     THEN(ReturnsAllTheScores))
{
    auto const now = std::chrono::system_clock::now();

    auto s1 = score_record{"p1", 1, now + std::chrono::hours(2)};    
    auto s2 = score_record{"p2", 5, now + std::chrono::hours(1)};
    auto s3 = score_record{"p3", 3, now + std::chrono::hours(3)};
    auto s4 = score_record{"p1", 3, now + std::chrono::hours(2)};

    this->rankings.add_score(s1);
    this->rankings.add_score(s2);
    this->rankings.add_score(s3);
    this->rankings.add_score(s4);

    auto const all_scores = this->rankings.get_top_scores(5);

    ASSERT_THAT(all_scores.size(), Eq(4u));

    EXPECT_THAT(all_scores[0], Eq(s2));
    EXPECT_THAT(all_scores[1], Eq(s4));
    EXPECT_THAT(all_scores[2], Eq(s3));
    EXPECT_THAT(all_scores[3], Eq(s1));
}

TEST_THAT(HighScoresRankings,
     WHAT(GetTopScores),
     WHEN(GivenANumberNLessThanTheTotalNumberOfScores),
     THEN(ReturnsTheTopNScoresOnly))
{
    auto const now = std::chrono::system_clock::now();

    auto s1 = score_record{"p1", 1, now + std::chrono::hours(2)};    
    auto s2 = score_record{"p2", 5, now + std::chrono::hours(1)};
    auto s3 = score_record{"p3", 3, now + std::chrono::hours(3)};
    auto s4 = score_record{"p1", 3, now + std::chrono::hours(2)};

    this->rankings.add_score(s1);
    this->rankings.add_score(s2);
    this->rankings.add_score(s3);
    this->rankings.add_score(s4);

    auto const all_scores = this->rankings.get_top_scores(3);

    ASSERT_THAT(all_scores.size(), Eq(3u));

    EXPECT_THAT(all_scores[0], Eq(s2));
    EXPECT_THAT(all_scores[1], Eq(s4));
    EXPECT_THAT(all_scores[2], Eq(s3)); 
}

TEST_THAT(HighScoresRankings, 
     WHAT(Clear),
     WHEN(Always),
     THEN(DeletesAllTheRecordedScores))
{
    auto const now = std::chrono::system_clock::now();

    auto s1 = score_record{"p1", 1, now + std::chrono::hours(2)};    
    auto s2 = score_record{"p2", 5, now + std::chrono::hours(1)};
    auto s3 = score_record{"p3", 3, now + std::chrono::hours(3)};
    auto s4 = score_record{"p1", 3, now + std::chrono::hours(2)};

    this->rankings.add_score(s1);
    this->rankings.add_score(s2);
    this->rankings.add_score(s3);
    this->rankings.add_score(s4);

    this->rankings.clear();

    auto const all_scores = this->rankings.get_top_scores(3);

    EXPECT_TRUE(all_scores.empty());
}

} }
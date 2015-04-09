#include "stdafx.hpp"

#include "snake_overflow/score_record.hpp"

namespace snake_overflow
{

using ::testing::Lt;
using ::testing::Test;

class ScoreRecord : public Test
{
};

TEST_THAT(ScoreRecord,
     WHAT(LessThanComparisonOperator),
     WHEN(GivenALeftHandScoreThatHasLessPointsThanTheRightHandScore),
     THEN(ReturnsTrue))
{
    auto const now = std::chrono::system_clock::now();

    auto const s1 = score_record{"p1", 100, now};

    auto const s2 = score_record{"p1", 200, now};

    EXPECT_THAT(s1, Lt(s2));
}

TEST_THAT(ScoreRecord,
     WHAT(LessThanComparisonOperator),
     WHEN(GivenALHScoreThatHasLessPointsThanTheRHScoreButIsMoreRecent),
     THEN(ReturnsTrue))
{
    auto const now = std::chrono::system_clock::now();

    now + std::chrono::hours(1);

    auto const s1 = score_record{"p1", 100, now + std::chrono::hours(2)};

    auto const s2 = score_record{"p1", 200, now + std::chrono::hours(1)};

    EXPECT_THAT(s1, Lt(s2));
}

TEST_THAT(ScoreRecord,
     WHAT(LessThanComparisonOperator),
     WHEN(GivenALHScoreThatHasTheSamePointsAsTheRHScoreButIsMoreRecent),
     THEN(ReturnsTrue))
{
    auto const now = std::chrono::system_clock::now();

    now + std::chrono::hours(1);

    auto const s1 = score_record{"p1", 100, now + std::chrono::hours(2)};

    auto const s2 = score_record{"p1", 100, now + std::chrono::hours(1)};

    EXPECT_THAT(s1, Lt(s2));
}

}
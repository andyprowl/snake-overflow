#include "stdafx.hpp"

#include "snake_overflow/score_record.hpp"
#include <tuple>

namespace snake_overflow
{

score_record::score_record(
    std::string player_name, 
    int const points,
    util::value_ref<std::chrono::system_clock::time_point> date)
    : player_name(std::move(player_name))
    , points{points}
    , date{date}
{
}

bool operator == (util::value_ref<score_record> lhs, 
                  util::value_ref<score_record> rhs)
{
    return ((lhs.player_name == rhs.player_name) &&
            (lhs.points == rhs.points) &&
            (lhs.date == rhs.date));
}

bool operator != (util::value_ref<score_record> lhs, 
                  util::value_ref<score_record> rhs)
{
    return !(lhs == rhs);
}

bool operator < (util::value_ref<score_record> lhs, 
                 util::value_ref<score_record> rhs)
{
    if (lhs.points == rhs.points)
    {
        if (lhs.date == rhs.date)
        {
            return lhs.player_name < rhs.player_name;
        }

        return lhs.date > rhs.date;
    }
    
    return lhs.points < rhs.points;
}

bool operator > (util::value_ref<score_record> lhs, 
                 util::value_ref<score_record> rhs)
{
    if (lhs.points == rhs.points)
    {
        if (lhs.date == rhs.date)
        {
            return lhs.player_name > rhs.player_name;
        }

        return lhs.date < rhs.date;
    }
    
    return lhs.points > rhs.points;
}

}
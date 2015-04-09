#pragma once

#include "util/value_ref.hpp"
#include <chrono>
#include <string>

namespace snake_overflow
{

struct score_record
{

public:

    score_record(std::string player_name, 
                 int points, 
                 util::value_ref<std::chrono::system_clock::time_point> date);

public:

    std::string player_name;

    int points;

    std::chrono::system_clock::time_point date;

};

bool operator == (util::value_ref<score_record> lhs, 
                  util::value_ref<score_record> rhs);

bool operator != (util::value_ref<score_record> lhs, 
                  util::value_ref<score_record> rhs);

bool operator < (util::value_ref<score_record> lhs, 
                 util::value_ref<score_record> rhs);

bool operator > (util::value_ref<score_record> lhs, 
                 util::value_ref<score_record> rhs);

}
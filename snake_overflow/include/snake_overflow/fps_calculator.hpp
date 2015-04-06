#pragma once

#include <chrono>

namespace snake_overflow
{

class fps_calculator
{

public:

    fps_calculator();

    fps_calculator(fps_calculator const&) = delete;

    fps_calculator(fps_calculator&&) = delete;

    fps_calculator& operator = (fps_calculator const&) = delete;

    fps_calculator& operator = (fps_calculator&&) = delete;

    operator float () const;

    ~fps_calculator() = default;

    void update();

    float get_current_fps() const;

private:

    std::chrono::time_point<std::chrono::system_clock> last_frame_time;

    float current_fps = 60.0;

};

}
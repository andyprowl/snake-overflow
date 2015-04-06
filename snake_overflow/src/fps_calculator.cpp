#include "stdafx.hpp"

#include "snake_overflow/fps_calculator.hpp"

namespace snake_overflow
{

fps_calculator::fps_calculator()
{
    this->last_frame_time = std::chrono::system_clock::now();
}

fps_calculator::operator float () const
{
    return this->current_fps;
}

void fps_calculator::update()
{
    auto const time = std::chrono::system_clock::now();
     
    auto const elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        time - this->last_frame_time);

    this->current_fps = 1000.f / elapsed.count();

    this->last_frame_time = time;
}

float fps_calculator::get_current_fps() const
{
    return this->current_fps;
}

}
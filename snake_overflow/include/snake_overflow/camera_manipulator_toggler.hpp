#pragma once

namespace snake_overflow
{

class camera_manipulator_toggler
{

public:
   
    virtual ~camera_manipulator_toggler() = default;

    virtual camera_manipulator& get_current_manipulator() const = 0;

    virtual void activate_next_camera_manipulator() = 0;

};

}
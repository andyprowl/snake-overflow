#pragma once

#include "snake_overflow/zooming_camera_manipulator.hpp"
#include <cinder/Camera.h>

namespace snake_overflow
{

struct camera_view;

class snake;

class auto_follow_camera_manipulator : public zooming_camera_manipulator
{

public:

    auto_follow_camera_manipulator(snake const& s);

    virtual void on_resize() override;

private:

    camera_view get_camera_view() const;

private:

    snake const& hero;

};

}
#pragma once

#include "cinder/Arcball.h"
#include "cinder/Camera.h"

namespace snake_overflow
{

struct camera_view;

class snake;

class camera_manipulator
{

public:

    camera_manipulator();

    void set_camera_matrices(snake const& s);

    bool is_auto_follow_on() const;

    void toggle_auto_follow();

    void begin_arcball_drag(cinder::Vec2i mouse_xy);

    void continue_arcball_drag(cinder::Vec2i mouse_xy);

    void zoom(float amount);

    void reset();

private:

    void setup_arcball_manipulator();

    camera_view get_camera_view() const;

    camera_view get_auto_follow_camera_view(snake const& s) const;

private:

    cinder::CameraPersp camera;
    
    float camera_distance;

    float zoom_factor = 20.f;

    cinder::Arcball arcball;

    bool auto_follow;

};

}
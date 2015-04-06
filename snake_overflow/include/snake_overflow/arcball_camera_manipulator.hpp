#pragma once

#include "snake_overflow/zooming_camera_manipulator.hpp"
#include <cinder/Arcball.h>
#include <cinder/Camera.h>

namespace snake_overflow
{

struct camera_view;

class arcball_camera_manipulator : public zooming_camera_manipulator
{

public:

    arcball_camera_manipulator();

    virtual void set_camera_matrices() override;

    virtual void on_resize() override;

    void set_camera_orientation(cinder::Quatf rot);

    void begin_arcball_drag(cinder::Vec2i mouse_xy);

    void continue_arcball_drag(cinder::Vec2i mouse_xy);

    void reset_camera();

private:

    camera_view get_camera_view() const;

private:

    cinder::Arcball arcball;

};

}
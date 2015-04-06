#pragma once

#include "snake_overflow/camera_manipulator.hpp"
#include <cinder/Camera.h>

namespace snake_overflow
{

struct camera_view;

class snake;

class zooming_camera_manipulator : public camera_manipulator
{

public:
    
    zooming_camera_manipulator();

    virtual void set_camera_matrices() override;

    virtual void zoom(float amount) override;

    virtual cinder::Quatf get_camera_orientation() const override;

    void reset_camera_zoom();

    float get_camera_zoom() const;

protected:

private:

    virtual camera_view get_camera_view() const = 0;

private:

    cinder::CameraPersp camera;
    
    float camera_distance;

    float zoom_factor = 20.f;

};

}
#pragma once

namespace snake_overflow
{

class camera_manipulator
{

public:

    virtual ~camera_manipulator() = default;

    virtual void set_camera_matrices() = 0;

    virtual void zoom(float amount) = 0;

    virtual void on_resize() = 0;

    virtual cinder::Quatf get_camera_orientation() const = 0;

};

}
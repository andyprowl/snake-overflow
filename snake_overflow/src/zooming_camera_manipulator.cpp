#include "stdafx.hpp"

#include "snake_overflow/zooming_camera_manipulator.hpp"
#include "snake_overflow/camera_view.hpp"

namespace snake_overflow
{

static auto const initial_camera_distance = 600.f;

zooming_camera_manipulator::zooming_camera_manipulator()
    : camera_distance{initial_camera_distance}
{
}

void zooming_camera_manipulator::set_camera_matrices()
{
    auto const view = get_camera_view();

    auto const ratio = cinder::app::getWindowAspectRatio();

    this->camera.setPerspective(60.0f, ratio, 5.f, 3000.f);
    
    this->camera.lookAt(view.eye, view.center, view.up);
    
    cinder::gl::setMatrices(this->camera);
}

void zooming_camera_manipulator::zoom(float const amount)
{
    this->camera_distance -= amount * this->zoom_factor;
}

cinder::Quatf zooming_camera_manipulator::get_camera_orientation() const
{
    return this->camera.getOrientation();
}

void zooming_camera_manipulator::reset_camera_zoom()
{
    this->camera_distance = initial_camera_distance;
}

float zooming_camera_manipulator::get_camera_zoom() const
{
    return this->camera_distance;
}

}
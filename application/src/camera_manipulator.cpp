#include "stdafx.hpp"

#include "snake_overflow/camera_manipulator.hpp"
#include "snake_overflow/camera_view.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/snake.hpp"

namespace snake_overflow
{

camera_manipulator::camera_manipulator()
    : auto_follow{false}
{
    setup_arcball_manipulator();
}

void camera_manipulator::set_camera_matrices(snake const& s)
{
    auto const view = this->auto_follow ? get_auto_follow_camera_view(s)
                                        : get_camera_view();

    auto const ratio = cinder::app::getWindowAspectRatio();

    this->camera.setPerspective(60.0f, ratio, 5.f, 3000.f);
    
    this->camera.lookAt(view.eye, view.center, view.up);
    
    cinder::gl::setMatrices(this->camera);

    if (!this->auto_follow)
    {
        cinder::gl::rotate(this->arcball.getQuat());
    }
}

bool camera_manipulator::is_auto_follow_on() const
{
    return this->auto_follow;
}

void camera_manipulator::toggle_auto_follow()
{
    this->auto_follow = !(this->auto_follow); 

    if (!this->auto_follow) 
    {
        auto rot = this->camera.getOrientation();
            
        rot = cinder::Quatf{rot.getAxis(), -rot.getAngle()};

        this->arcball.setQuat(rot);
    }
}

void camera_manipulator::begin_arcball_drag(cinder::Vec2i mouse_xy)
{
    auto const bounds = cinder::app::getWindowBounds();

    auto const bottom = static_cast<int>(bounds.getLR().y);

    this->arcball.mouseDown({mouse_xy.x, bottom - mouse_xy.y});
}

void camera_manipulator::continue_arcball_drag(cinder::Vec2i mouse_xy)
{
    auto const bounds = cinder::app::getWindowBounds();

    auto const bottom = static_cast<int>(bounds.getLR().y);

    this->arcball.mouseDrag({mouse_xy.x, bottom - mouse_xy.y});
}

void camera_manipulator::zoom(float const amount)
{
    this->camera_distance -= amount * this->zoom_factor;
}

void camera_manipulator::setup_arcball_manipulator()
{
    this->arcball.setWindowSize(cinder::app::getWindowSize());

    this->arcball.setCenter(cinder::app::getWindowCenter());
    
    this->arcball.setRadius(150);
}

camera_view camera_manipulator::get_camera_view() const
{
    auto const eye = cinder::Vec3f{0.f, 0.f, this->camera_distance};

    auto const center = cinder::Vec3f::zero();

    auto const up = cinder::Vec3f::yAxis();

    return {eye, center, up};
}

camera_view camera_manipulator::get_auto_follow_camera_view(
    snake const& s) const
{
    auto head = s.get_body().get_trail_head();

    auto pos = get_footprint_position(head.step);

    auto const normalized_eye = vec3f_from_point(pos.location).normalized();

    auto const eye = normalized_eye * this->camera_distance;

    auto const center = cinder::Vec3f::zero();

    auto const n = normalized_eye.cross(cinder::Vec3f::xAxis());

    auto const up = (n == cinder::Vec3f::zero()) ? normalized_eye : n;

    return {eye, center, up};
}

}
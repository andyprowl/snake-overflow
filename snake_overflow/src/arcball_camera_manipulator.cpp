#include "stdafx.hpp"

#include "snake_overflow/arcball_camera_manipulator.hpp"
#include "snake_overflow/camera_view.hpp"

namespace snake_overflow
{
    
arcball_camera_manipulator::arcball_camera_manipulator()
{
    on_resize();
}

void arcball_camera_manipulator::reset_camera()
{
    reset_camera_zoom();

    this->arcball.resetQuat();
}

void arcball_camera_manipulator::set_camera_matrices()
{
    zooming_camera_manipulator::set_camera_matrices();

    cinder::gl::rotate(this->arcball.getQuat());
}

void arcball_camera_manipulator::on_resize()
{
    this->arcball.setWindowSize(cinder::app::getWindowSize());

    this->arcball.setCenter(cinder::app::getWindowCenter());
    
    this->arcball.setRadius(150);
}

void arcball_camera_manipulator::set_camera_orientation(
    cinder::Quatf const rot)
{
    this->arcball.setQuat(rot);
}

void arcball_camera_manipulator::begin_arcball_drag(
    cinder::Vec2i const mouse_xy)
{
    auto const bounds = cinder::app::getWindowBounds();

    auto const bottom = static_cast<int>(bounds.getLR().y);

    this->arcball.mouseDown({mouse_xy.x, bottom - mouse_xy.y});
}

void arcball_camera_manipulator::continue_arcball_drag(
    cinder::Vec2i const mouse_xy)
{
    auto const bounds = cinder::app::getWindowBounds();

    auto const bottom = static_cast<int>(bounds.getLR().y);

    this->arcball.mouseDrag({mouse_xy.x, bottom - mouse_xy.y});
}

camera_view arcball_camera_manipulator::get_camera_view() const
{
    auto const eye = cinder::Vec3f{0.f, 0.f, get_camera_zoom()};

    auto const center = cinder::Vec3f::zero();

    auto const up = cinder::Vec3f::yAxis();

    return {eye, center, up};
}

}
#include "stdafx.hpp"

#include "snake_overflow/auto_follow_camera_manipulator.hpp"
#include "snake_overflow/camera_view.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/snake.hpp"

namespace snake_overflow
{
    
auto_follow_camera_manipulator::auto_follow_camera_manipulator(snake const& s)
    : hero{s}
{
}

void auto_follow_camera_manipulator::on_resize()
{
}

camera_view auto_follow_camera_manipulator::get_camera_view() const
{
    auto head = this->hero.get_body().get_trail_head();

    auto pos = get_footprint_position(head.step);

    auto const normalized_eye = vec3f_from_point(pos.location).normalized();

    auto const eye = normalized_eye * get_camera_zoom();

    auto const center = cinder::Vec3f::zero();

    auto const n = normalized_eye.cross(cinder::Vec3f::xAxis());

    auto const up = (n == cinder::Vec3f::zero()) ? normalized_eye : n;

    return {eye, center, up};
}

}
#include "stdafx.hpp"

#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/snake_renderer.hpp"
#include "snake_overflow/snake.hpp"
#include "util/sequence.hpp"
#include <cassert>

namespace snake_overflow
{

snake_renderer::snake_renderer(float const snake_width, 
                               float const snake_height,
                               float const block_size)
    : width{snake_width}
    , height{snake_height}
    , block_size{block_size}
{
}

void snake_renderer::render(util::value_ref<snake> s) const
{
    auto const trail = s.get_trail();

    for (auto const d : trail)
    {
        render_snake_part(d);
    }
}

void snake_renderer::render_snake_part(util::value_ref<dynamics> d) const
{    
    auto const rotation = compute_snake_part_rotation(d);

    auto const translation = compute_snake_part_translation(d);

    draw_snake_part(rotation, translation);
}

cinder::Vec3f snake_renderer::compute_snake_part_translation(
    util::value_ref<dynamics> d) const
{
    auto const pos = get_dynamics_position(d);

    auto const normal = get_face_normal_vector(pos.face);
    
    auto const block_origin = vec3f_from_point(pos.location) * this->block_size;

    auto const surface_offset = normal * this->block_size / 2;

    return block_origin + surface_offset;
}

cinder::Quatf snake_renderer::compute_snake_part_rotation(
    util::value_ref<dynamics> d) const
{
    auto const normal = get_face_normal_vector(d.profile.face);
    
    auto const normal_rotation = cinder::Quatf{cinder::Vec3f::zAxis(), normal};

    auto const direction = get_dynamics_direction_vector(d);

    auto const direction_rotation = cinder::Quatf{
        normal_rotation * cinder::Vec3f::yAxis(), 
        vec3f_from_point(direction)};

    return normal_rotation * direction_rotation;
}

cinder::Vec3f snake_renderer::get_face_normal_vector(
    block_face const face) const
{
    auto const n = get_face_normal(face);

    return vec3f_from_point(n);
}

cinder::Vec3f snake_renderer::get_snake_part_sizes() const
{
    return {this->width, this->block_size, this->height};
}

void snake_renderer::draw_snake_part(
    util::value_ref<cinder::Quatf> rotation, 
    util::value_ref<cinder::Vec3f> translation) const
{
    cinder::gl::translate(translation);

    cinder::gl::rotate(rotation);

    draw_snake_part_shape();

    cinder::gl::rotate(rotation.inverse());

    cinder::gl::translate(translation.inverse());
}

void snake_renderer::draw_snake_part_shape() const
{
    cinder::gl::color(cinder::Color{1.f, 0.f, 0.f});

    cinder::gl::drawCube(cinder::Vec3f::zero(), get_snake_part_sizes());
}

}
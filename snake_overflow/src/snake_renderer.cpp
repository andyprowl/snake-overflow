#include "stdafx.hpp"

#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/snake_renderer.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/texture_binder.hpp"
#include "snake_overflow/texture_repository.hpp"
#include "util/sequence.hpp"
#include "util/wave.hpp"
#include <cassert>

namespace snake_overflow
{

snake_renderer::snake_renderer(float const snake_width, 
                               float const snake_height,
                               float const block_size,
                               texture_repository const& textures)
    : width{snake_width}
    , height{snake_height}
    , block_size{block_size}
    , textures{textures}
{
}

void snake_renderer::set_current_snake(snake const& s)
{
    this->hero = &s;

    this->skin = this->textures.get_texture(s.skin);
}

void snake_renderer::render() const
{
    auto const binder = texture_binder{this->skin};
    
    auto const color = get_snake_color(*(this->hero));

    cinder::gl::color(color);

    auto const trail = this->hero->get_body().get_trail();

    auto const length = this->hero->get_length();

    for (auto const i : util::sequence(0, length))
    {
        auto const is_edge_winding = is_trail_winding_around_edge(trail, i);

        render_snake_part(trail[i], (i == length - 1), is_edge_winding);
    }
}

void snake_renderer::set_skin(cinder::gl::Texture skin)
{
    this->skin = std::move(skin);
}

bool snake_renderer::is_trail_winding_around_edge(
    util::value_ref<std::vector<dynamics>> trail, 
    int const i) const
{
    if (i == trail.size() - 1) return false;

    return ((trail[i].action ==  maneuvre::straight_move) &&
            (trail[i].step.profile.face != trail[i + 1].step.profile.face));
}

void snake_renderer::render_snake_part(util::value_ref<dynamics> d,
                                       bool const is_head,
                                       bool const is_edge_winding) const
{    
    auto const rotation = compute_snake_part_rotation(d);

    auto const translation = compute_snake_part_translation(d);

    draw_snake_part(rotation, translation, d, is_head, is_edge_winding);
}

cinder::Quatf snake_renderer::compute_snake_part_rotation(
    util::value_ref<dynamics> d) const
{
    auto const normal = get_face_normal_vector(d.step.profile.face);
    
    auto const normal_rotation = cinder::Quatf{cinder::Vec3f::zAxis(), normal};

    auto const direction = get_footprint_direction_vector(d.step);

    auto const direction_rotation = cinder::Quatf{
        cinder::Vec3f::yAxis() * normal_rotation, 
        vec3f_from_point(direction)};

    return normal_rotation * direction_rotation;
}

cinder::Vec3f snake_renderer::compute_snake_part_translation(
    util::value_ref<dynamics> d) const
{
    auto const pos = get_footprint_position(d.step);

    auto const normal = get_face_normal_vector(pos.face);
    
    auto const block_origin = vec3f_from_point(pos.location) * this->block_size;

    auto const surface_offset = normal * this->block_size / 2;

    return block_origin + surface_offset;
}

cinder::Vec3f snake_renderer::get_face_normal_vector(
    block_face const face) const
{
    auto const n = get_face_normal(face);

    return vec3f_from_point(n);
}

void snake_renderer::draw_snake_part(
    util::value_ref<cinder::Quatf> rotation, 
    util::value_ref<cinder::Vec3f> translation,
    util::value_ref<dynamics> d,
    bool const is_head,
    bool const is_edge_winding) const
{
    cinder::gl::pushModelView();

    cinder::gl::translate(translation);

    cinder::gl::rotate(rotation);

    draw_snake_part_shape(d, is_head, is_edge_winding);

    cinder::gl::popModelView();
}

void snake_renderer::draw_snake_part_shape(util::value_ref<dynamics> d,
                                           bool const is_head,
                                           bool const is_edge_winding) const
{
    if (is_head)
    {
        draw_head();
    }
    else
    {
        draw_inner_part(d, is_edge_winding);
    }
}

void snake_renderer::draw_inner_part(util::value_ref<dynamics> d,
                                     bool const is_edge_winding) const
{
    switch (d.action)
    {
        case maneuvre::straight_move:
        {
            return draw_inner_part_on_forward_movement(is_edge_winding);
        }

        case maneuvre::left_turn:
        {
            return draw_inner_part_on_left_turn(d);
        }

        case maneuvre::right_turn:
        {
            return draw_inner_part_on_right_turn(d);
        }

        default:
        {
            assert(false);
        }
    }
}

void snake_renderer::draw_inner_part_on_forward_movement(
    bool const is_edge_winding) const
{
    auto const sizes = get_snake_inner_part_sizes(is_edge_winding);

    cinder::gl::drawCube(cinder::Vec3f::zero(), sizes);
}

void snake_renderer::draw_inner_part_on_left_turn(
    util::value_ref<dynamics> d) const
{
    auto const margin = (this->block_size - this->width) / 2;

    auto const length = this->block_size - margin;

    cinder::gl::drawCube({0.f, -margin / 2.f, 0.f}, 
                         {this->width, length, this->height});

    // SHAME ON THE AUTHOR!
    // This check is due to a fail. I probably got the maths wrong at some 
    // point, and without this, right turns are not rendered properly on top and 
    // bottom faces of a block.
    if (((d.step.profile.face == block_face::top) || 
         (d.step.profile.face == block_face::bottom)) && 
        (d.step.profile.direction == canonical_direction::negative_y()))
    {
        cinder::gl::drawCube({+(this->block_size - margin) / 2.f, 0.f, 0.f}, 
                             {margin, this->width, this->height});
    }
    else
    {
        cinder::gl::drawCube({-(this->block_size - margin) / 2.f, 0.f, 0.f}, 
                             {margin, this->width, this->height});
    }
}

void snake_renderer::draw_inner_part_on_right_turn(
    util::value_ref<dynamics> d) const
{
    auto const margin = (this->block_size - this->width) / 2;

    auto const length = this->block_size - margin;

    cinder::gl::drawCube({0.f, -margin / 2.f, 0.f}, 
                         {this->width, length, this->height});

    // SHAME ON THE AUTHOR!
    // This check is due to a fail. I probably got the maths wrong at some 
    // point, and without this, right turns are not rendered properly on top and 
    // bottom faces of a block.
    if (((d.step.profile.face == block_face::top) || 
         (d.step.profile.face == block_face::bottom)) && 
        (d.step.profile.direction == canonical_direction::negative_y()))
    {
        cinder::gl::drawCube({-(this->block_size - margin) / 2.f, 0.f, 0.f}, 
                             {margin, this->width, this->height});
    }
    else
    {
        cinder::gl::drawCube({(this->block_size - margin) / 2.f, 0.f, 0.f}, 
                             {margin, this->width, this->height});
    }
}

void snake_renderer::draw_head() const
{
    auto sizes = get_snake_inner_part_sizes(false);

    cinder::gl::color(cinder::Color{1.f, 0.f, 0.f});

    cinder::gl::drawCube({0.f, -sizes.y / 4.f, 0.f}, sizes);
}

cinder::Vec3f snake_renderer::get_snake_inner_part_sizes(
    bool const is_edge_winding) const
{
    if (is_edge_winding)
    {
        return {this->width, this->block_size + this->height, this->height};
    }
    else
    {
        return {this->width, this->block_size, this->height};
    }
}

cinder::Color snake_renderer::get_snake_color(util::value_ref<snake> s) const
{
    if (s.invulnerability_bonus)
    {
        auto const factor = cinder::app::getElapsedFrames() * 0.2f;

        auto const c = util::wave(factor, 0.f, 1.f);

        return {1.f, c, c};
    }
    else
    {
        return cinder::Color::white();
    }
}

}
#pragma once

#include "util/value_ref.hpp"
#include <cinder/gl/Texture.h>

namespace snake_overflow
{

enum class block_face;

struct canonical_direction;
struct dynamics;

class snake;
class texture_repository;

class snake_renderer
{

public:

    snake_renderer(float snake_width, 
                   float snake_height, 
                   float block_size,
                   texture_repository const& textures);

    void set_current_snake(snake const& s);

    void render() const;

    void set_skin(cinder::gl::Texture skin);

private:

    bool is_trail_winding_around_edge(
        util::value_ref<std::vector<dynamics>> trail, 
        int const i) const;

    void render_snake_part(util::value_ref<dynamics> pos, 
                           bool is_head,
                           bool is_edge_winding) const;

    cinder::Quatf compute_snake_part_rotation(
        util::value_ref<dynamics> d) const;

    cinder::Vec3f compute_snake_part_translation(
        util::value_ref<dynamics> d) const;

    cinder::Vec3f get_face_normal_vector(block_face face) const;

    void draw_snake_part(util::value_ref<cinder::Quatf> rotation, 
                         util::value_ref<cinder::Vec3f> translation,
                         util::value_ref<dynamics> d,
                         bool is_head,
                         bool is_edge_winding) const;

    void draw_snake_part_shape(util::value_ref<dynamics> d, 
                               bool is_head,
                               bool is_edge_winding) const;

    void draw_inner_part(util::value_ref<dynamics> d,
                         bool is_edge_winding) const;

    void draw_inner_part_on_forward_movement(bool is_edge_winding) const;

    void draw_inner_part_on_left_turn(util::value_ref<dynamics> d) const;

    void draw_inner_part_on_right_turn(util::value_ref<dynamics> d) const;

    void draw_head() const;

    cinder::Vec3f get_snake_inner_part_sizes(bool is_edge_winding) const;

    cinder::Color get_snake_color(util::value_ref<snake> s) const;

private:

    snake const* hero = nullptr;

    float width;

    float height;

    float block_size;

    cinder::gl::Texture skin;

    texture_repository const& textures;

};

}
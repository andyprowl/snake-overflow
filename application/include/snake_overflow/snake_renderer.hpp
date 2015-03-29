#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

enum class block_face;

struct canonical_direction;
struct dynamics;

class snake;

class snake_renderer
{

public:

    snake_renderer(float snake_width, float snake_height, float block_size);

    void render(util::value_ref<snake> s) const;

private:

    void render_snake_part(util::value_ref<dynamics> pos, bool is_head) const;

    cinder::Quatf compute_snake_part_rotation(
        util::value_ref<dynamics> d) const;

    cinder::Vec3f compute_snake_part_translation(
        util::value_ref<dynamics> pos) const;

    cinder::Vec3f get_face_normal_vector(block_face face) const;

    void draw_snake_part(util::value_ref<cinder::Quatf> rotation, 
                         util::value_ref<cinder::Vec3f> translation,
                         bool is_head) const;

    void draw_snake_part_shape(bool is_head) const;

    void draw_inner_body_part() const;

    void draw_head() const;

    cinder::Vec3f get_snake_inner_part_sizes() const;

private:

    float width;

    float height;

    float block_size;

};

}
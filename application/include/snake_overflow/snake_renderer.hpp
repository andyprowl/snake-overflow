#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

enum class block_face;

struct canonical_direction;
struct dynamics;
struct position;

class snake;

class snake_renderer
{

public:

    snake_renderer(float snake_width, float snake_height, float block_size);

    void render(util::value_ref<snake> s) const;

private:

    void render_snake_part(util::value_ref<dynamics> pos) const;

    cinder::Vec3f get_snake_part_placement(util::value_ref<position> pos) const;

    cinder::Quatf get_snake_part_rotation(util::value_ref<dynamics> d) const;

    cinder::Vec3f get_face_normal_vector(block_face face) const;

    cinder::Vec3f get_snake_part_sizes() const;

    void draw_snake_part_shape() const;

private:

    float width;

    float height;

    float block_size;

};

}
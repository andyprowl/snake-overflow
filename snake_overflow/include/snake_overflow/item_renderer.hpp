#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

class fruit;
class item;
class terrain;
class texture_repository;

class item_renderer
{

public:

    item_renderer(float block_size, texture_repository const& textures);

    void render(util::value_ref<terrain> t) const;

private:

    void render_item(util::value_ref<item> i) const;

    void render_centered_item(util::value_ref<item> i, 
                         util::value_ref<cinder::Vec3f> center) const;

    void rotate_to_face_normal(util::value_ref<item> i) const;

    void draw_item_shape(util::value_ref<item> i) const;

    void draw_fruit_shape(util::value_ref<fruit> f) const;

    void draw_diet_pill_shape() const;

private:

    float block_size;

    texture_repository const& textures;

};

}
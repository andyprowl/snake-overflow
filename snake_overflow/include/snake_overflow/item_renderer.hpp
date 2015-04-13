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

    item_renderer(float block_size, 
                  texture_repository const& textures);

    void set_current_terrain(terrain const& ground);

    void render() const;

private:

    void render_item(util::value_ref<item> i) const;

    void render_centered_item(util::value_ref<item> i, 
                         util::value_ref<cinder::Vec3f> center) const;

    void rotate_to_face_normal(util::value_ref<item> i) const;

    void draw_item_shape(util::value_ref<item> i) const;

    void draw_fruit_shape(util::value_ref<fruit> f) const;

    void draw_diet_pill_shape() const;

    void draw_invulnerability_potion_shape() const;

    void draw_speed_booster_shape() const;

private:

    terrain const* ground = nullptr;

    float block_size;

    texture_repository const& textures;

};

}
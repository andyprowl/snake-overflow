#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

class diet_pill;
class fruit;
class invulnerability_potion;
class item;
class speed_booster;
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

    void draw_diet_pill_shape(util::value_ref<diet_pill> p) const;

    void draw_invulnerability_potion_shape(
        util::value_ref<invulnerability_potion> p) const;

    void draw_speed_booster_shape(util::value_ref<speed_booster> b) const;

private:

    terrain const* ground = nullptr;

    float block_size;

    texture_repository const& textures;

};

}
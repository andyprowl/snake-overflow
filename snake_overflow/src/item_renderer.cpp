#include "stdafx.hpp"

#include "snake_overflow/diet_pill.hpp"
#include "snake_overflow/fruit.hpp"
#include "snake_overflow/invulnerability_potion.hpp"
#include "snake_overflow/item.hpp"
#include "snake_overflow/item_renderer.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/speed_booster.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/texture_binder.hpp"
#include "util/wave.hpp"

namespace snake_overflow
{

item_renderer::item_renderer(float const block_size, 
                             texture_repository const& textures)
    : block_size{block_size}
    , textures{textures}
{
}

void item_renderer::set_current_terrain(terrain const& ground)
{
    this->ground = &ground;
}

void item_renderer::render() const
{
    this->ground->for_each_item([this] (util::value_ref<item> i)
    {
        render_item(i);
    });
}

void item_renderer::render_item(util::value_ref<item> i) const
{
    auto const pos = i.get_position();

    auto const origin = vec3f_from_point(pos.location) * this->block_size;

    auto const n = vec3f_from_point(get_face_normal(pos.face));
    
    auto const floater = util::wave(cinder::app::getElapsedSeconds() + 
                                    origin.x + 
                                    origin.y +
                                    origin.z, 
                                    0.8f, 
                                    1.0f);

    auto const center = origin + n * (this->block_size * floater);

    render_centered_item(i, center);
}

void item_renderer::render_centered_item(
    util::value_ref<item> i,
    util::value_ref<cinder::Vec3f> center) const
{
    cinder::gl::pushModelView();

    cinder::gl::translate(center);

    rotate_to_face_normal(i);

    draw_item_shape(i);

    cinder::gl::popModelView();
}

void item_renderer::rotate_to_face_normal(util::value_ref<item> i) const
{
    auto const pos = i.get_position();
    
    auto const n = vec3f_from_point(get_face_normal(pos.face));
    
    // SHAME ON THE AUTHOR!
    // This check is due to a fail. I probably got the maths wrong at some 
    // point, and without this, items that are placed on left and right block
    // faces are not rotated correctly.
    if ((pos.face == block_face::left) || (pos.face == block_face::right))
    {
        cinder::gl::rotate(cinder::Quatf{n, -cinder::Vec3f::xAxis()});
    }
    else
    {
        cinder::gl::rotate(cinder::Quatf{n, cinder::Vec3f::xAxis()});
    }
}

void item_renderer::draw_item_shape(util::value_ref<item> i) const
{
    auto f = dynamic_cast<fruit const*>(&i);
    if (f != nullptr)
    {
        return draw_fruit_shape(*f);
    }

    auto dp = dynamic_cast<diet_pill const*>(&i);
    if (dp != nullptr)
    {
        return draw_diet_pill_shape(*dp);
    } 

    auto ip = dynamic_cast<invulnerability_potion const*>(&i);
    if (ip != nullptr)
    {
        return draw_invulnerability_potion_shape(*ip);
    }

    auto sb = dynamic_cast<speed_booster const*>(&i);
    if (sb != nullptr)
    {
        return draw_speed_booster_shape(*sb);
    }
}

void item_renderer::draw_fruit_shape(util::value_ref<fruit> f) const
{
    auto const color = cinder::ColorA{1.f, 1.f, 1.f, 1.f};

    cinder::gl::color(color);

    auto const radius = f.get_nutrition_value() * this->block_size / 15.f + 1.f;

    auto const capped_radius = std::min(radius, static_cast<float>(f.lifetime));

    auto const binder = texture_binder{this->textures, "apple"};

    cinder::gl::drawSphere(cinder::Vec3f::zero(), capped_radius, 24);
}

void item_renderer::draw_diet_pill_shape(util::value_ref<diet_pill> p) const
{
    auto const color = cinder::ColorA{1.f, 1.f, 1.f, 1.f};

    cinder::gl::color(color);

    auto const radius = this->block_size / 2;

    auto const capped_radius = std::min(radius, static_cast<float>(p.lifetime));

    auto const binder = texture_binder{this->textures, "pill2"};

    cinder::gl::drawCube(cinder::Vec3f::zero(), 
                         {capped_radius * 2, capped_radius, capped_radius});
}

void item_renderer::draw_invulnerability_potion_shape(
    util::value_ref<invulnerability_potion> p) const
{
    auto const color = cinder::ColorA{1.f, 1.f, 1.f, 1.f};

    cinder::gl::color(color);

    auto const radius = this->block_size / 3.f + 1.f;

    auto const capped_radius = std::min(radius, static_cast<float>(p.lifetime));

    auto const binder = texture_binder{this->textures, "invulnerability"};

    cinder::gl::drawSphere(cinder::Vec3f::zero(), capped_radius, 24);
}

void item_renderer::draw_speed_booster_shape(
    util::value_ref<speed_booster> b) const
{
    auto const color = cinder::ColorA{1.f, 1.f, 1.f, 1.f};

    cinder::gl::color(color);

    auto const radius = this->block_size / 3.f + 1.f;

    auto const capped_radius = std::min(radius, static_cast<float>(b.lifetime));

    auto const binder = texture_binder{this->textures, "bolt"};

    cinder::gl::drawSphere(cinder::Vec3f::zero(), capped_radius, 24);    
}

}
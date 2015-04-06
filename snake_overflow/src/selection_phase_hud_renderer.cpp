#include "stdafx.hpp"

#include "snake_overflow/selection_phase_hud_renderer.hpp"

namespace snake_overflow
{

selection_phase_hud_renderer::selection_phase_hud_renderer()
{
    create_fonts();
}

void selection_phase_hud_renderer::render(
    util::value_ref<std::string> map_name) const
{
    draw_title();

    draw_map_name(map_name);
}

void selection_phase_hud_renderer::create_fonts()
{
    this->map_name_font = cinder::Font{"Arial", 50.f};

    this->title_font = cinder::Font{"Arial", 35.f};
}

void selection_phase_hud_renderer::draw_title() const
{
    cinder::gl::enableAlphaBlending();

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    auto const color = cinder::ColorA{1.f, 1.f, 1.f, 1.f};
    
    auto const x_center = cinder::app::getWindowBounds().getCenter().x;

    auto const origin = cinder::Vec2f{x_center, 10.f};

    auto const text = "Choose a map (left/right arrows to change, "
                      "'Enter' to confirm)";

    cinder::gl::drawStringCentered(text, origin, color, this->title_font);

    cinder::gl::disableAlphaBlending();
}

void selection_phase_hud_renderer::draw_map_name(
    util::value_ref<std::string> map_name) const
{
    cinder::gl::enableAlphaBlending();

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    auto const color = cinder::ColorA{1.f, 1.f, 0.f, 1.f};
    
    auto const x_center = cinder::app::getWindowBounds().getCenter().x;

    auto const origin = cinder::Vec2f{x_center, 50.f};

    cinder::gl::drawStringCentered(map_name, 
                                   origin, 
                                   color, 
                                   this->map_name_font);

    cinder::gl::disableAlphaBlending();
}

}
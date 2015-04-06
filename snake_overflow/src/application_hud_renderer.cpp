#include "stdafx.hpp"

#include "snake_overflow/application_hud_renderer.hpp"

namespace snake_overflow
{

application_hud_renderer::application_hud_renderer()
    : show_fps{false}
{
    create_fonts();
}

void application_hud_renderer::render(float const fps)
{
    if (this->show_fps) 
    { 
        draw_fps_text(fps); 
    }
}

void application_hud_renderer::toogle_show_fps()
{
    this->show_fps = !(this->show_fps);
}
    
void application_hud_renderer::create_fonts()
{
    this->fps_text_font = cinder::Font{"Arial", 25.0};
}

void application_hud_renderer::draw_fps_text(float const fps) const
{
    cinder::gl::enableAlphaBlending();

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    auto const color = cinder::ColorA{1.f, 1.f, 0.f, 1.f};

    auto const text = get_fps_text(fps);

    auto const bottom_border = cinder::app::getWindowBounds().getLR().y;

    auto const origin = cinder::Vec2f{10.f, bottom_border - 30.f};

    cinder::gl::drawString(text, origin, color, this->fps_text_font);

    cinder::gl::disableAlphaBlending();
}

std::string application_hud_renderer::get_fps_text(float const fps) const
{
    return "FPS: " + std::to_string(fps);
}

}
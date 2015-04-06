#include "stdafx.hpp"

#include "snake_overflow/playing_phase_hud_renderer.hpp"

namespace snake_overflow
{

playing_phase_hud_renderer::playing_phase_hud_renderer()
    : show_fps{false}
{
    create_fonts();
}

void playing_phase_hud_renderer::render(float const fps,
                                        int const score,
                                        bool const is_game_paused, 
                                        bool const is_game_over,
                                        bool const is_auto_follow_on) const
{
    if (is_game_paused) { draw_pause_text(); }

    if (this->show_fps) { draw_fps_text(fps); }

    draw_score_text(score);

    if (is_game_over) { draw_game_over_text(); }

    if (is_auto_follow_on) { draw_auto_follow_text(); }
}

void playing_phase_hud_renderer::toogle_show_fps()
{
    this->show_fps = !(this->show_fps);
}
    
void playing_phase_hud_renderer::create_fonts()
{
    this->fps_text_font = cinder::Font{"Arial", 25.0};

    this->pause_text_font = cinder::Font{"Arial", 100.0};

    this->score_text_font = cinder::Font{"Arial", 50.0};

    this->game_over_text_font = cinder::Font{"Arial", 150.0};

    this->restart_text_font = cinder::Font{"Arial", 50.0};

    this->auto_follow_text_font = cinder::Font{"Arial", 25.0};
}

void playing_phase_hud_renderer::draw_pause_text() const
{
    cinder::gl::enableAlphaBlending();

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    auto const color = cinder::ColorA{1.f, 1.f, 0.f, 1.f};

    auto const text = "PAUSED";
    
    auto const right_border = cinder::app::getWindowBounds().getLR().x;

    auto const origin = cinder::Vec2f{right_border - 345.f, 10.f};

    cinder::gl::drawString(text, origin, color, this->pause_text_font);

    cinder::gl::disableAlphaBlending();
}

void playing_phase_hud_renderer::draw_fps_text(float const fps) const
{
    cinder::gl::enableAlphaBlending();

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    auto const color = cinder::ColorA{1.f, 1.f, 0.f, 1.f};

    auto const text = get_fps_text(fps);

    cinder::gl::drawString(text, {10., 10.}, color, this->fps_text_font);

    cinder::gl::disableAlphaBlending();
}

void playing_phase_hud_renderer::draw_score_text(int const score) const
{
    cinder::gl::enableAlphaBlending();

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    auto const color = cinder::ColorA{0.f, 1.f, 0.f, 1.f};

    auto const text = get_score_text(score);

    auto const bottom_border = cinder::app::getWindowBounds().getLR().y;

    auto const origin = cinder::Vec2f{10.f, bottom_border - 50.f};

    cinder::gl::drawString(text, origin, color, this->score_text_font);

    cinder::gl::disableAlphaBlending();
}

void playing_phase_hud_renderer::draw_game_over_text() const
{
    cinder::gl::enableAlphaBlending();

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    auto const center = cinder::app::getWindowBounds().getCenter() - 
                        cinder::Vec2f{0.f, 50.f};

    cinder::gl::drawStringCentered("GAME OVER", 
                                   center, 
                                   cinder::ColorA{1.f, 0.f, 0.f, 1.f}, 
                                   this->game_over_text_font);

    if ((int)cinder::app::getElapsedSeconds() % 2 == 0)
    {
        cinder::gl::drawStringCentered("Press ENTER or F5 to restart", 
                                       center + cinder::Vec2f{0.f, 140.f}, 
                                       cinder::ColorA{1.f, 1.f, 0.f, 1.f}, 
                                       this->restart_text_font);
    }

    cinder::gl::disableAlphaBlending();
}

void playing_phase_hud_renderer::draw_auto_follow_text() const
{
    cinder::gl::enableAlphaBlending();

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    auto const color = cinder::ColorA{1.f, 1.f, 1.f, 1.f};

    auto const text = "Auto-follow ON";

    auto const bottom_border = cinder::app::getWindowBounds().getLR().y;

    auto const right_border = cinder::app::getWindowBounds().getLR().x;

    auto const origin = cinder::Vec2f{right_border - 150.f, 
                                      bottom_border - 35.f};

    cinder::gl::drawString(text, origin, color, this->auto_follow_text_font);

    cinder::gl::disableAlphaBlending();
}

std::string playing_phase_hud_renderer::get_fps_text(float const fps) const
{
    return "FPS: " + std::to_string(fps);
}

std::string playing_phase_hud_renderer::get_score_text(int const score) const
{
    return "Score: " + std::to_string(score);
}

}
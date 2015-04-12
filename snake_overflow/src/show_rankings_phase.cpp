#include "stdafx.hpp"

#include "snake_overflow/application_state_machine.hpp"
#include "snake_overflow/game_map.hpp"
#include "snake_overflow/game_playing_phase.hpp"
#include "snake_overflow/high_scores_database.hpp"
#include "snake_overflow/map_selection_phase.hpp"
#include "snake_overflow/show_rankings_phase.hpp"
#include "snake_overflow/screen_resolution.hpp"
#include "util/sequence.hpp"
#include <cinder/ImageIo.h>
#include <cinder/Text.h>

namespace snake_overflow
{

show_rankings_phase::show_rankings_phase(
    application_state_machine& state_machine,
    high_scores_database const& rankings)
    : state_machine{state_machine}
    , rankings{rankings}
{
    load_parchment_image();
}

void show_rankings_phase::update()
{
}

void show_rankings_phase::draw()
{
    cinder::gl::clear({0.f, 0.f, 0.0f}, true);

    this->state_machine.get_game_playing_phase().draw();

    glClear(GL_DEPTH_BUFFER_BIT);

    cinder::gl::color(cinder::ColorA{1.f, 1.f, 1.f, 1.f});

    cinder::gl::enableAlphaBlending();

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    draw_rankings();

    cinder::gl::disableAlphaBlending();
}

void show_rankings_phase::on_keyboard_input(cinder::app::KeyEvent const e)
{
    if (e.getChar() == 'r')
    {
        switch_to_playing_phase();
    }
}

void show_rankings_phase::on_mouse_down(cinder::app::MouseEvent const e)
{
    auto& playing_phase = this->state_machine.get_game_playing_phase();

    playing_phase.on_mouse_down(e);
}

void show_rankings_phase::on_mouse_drag(cinder::app::MouseEvent const e)
{
    auto& playing_phase = this->state_machine.get_game_playing_phase();

    playing_phase.on_mouse_drag(e);
}

void show_rankings_phase::on_mouse_wheel(cinder::app::MouseEvent const e)
{
    auto& playing_phase = this->state_machine.get_game_playing_phase();

    playing_phase.on_mouse_wheel(e);
}

void show_rankings_phase::on_resize()
{
}

void show_rankings_phase::load_parchment_image()
{
    auto const asset = cinder::app::loadAsset("images/rankings.png");

    this->parchment_picture = cinder::loadImage(asset);    
}

void show_rankings_phase::draw_rankings() const
{
    draw_parchment();
    
    glClear(GL_DEPTH_BUFFER_BIT);

    draw_scores();    
}

void show_rankings_phase::draw_parchment() const
{
    auto const bounds = get_parchment_bounds();

    cinder::gl::draw(this->parchment_picture, bounds);
}

void show_rankings_phase::draw_scores() const
{
    auto const scores = get_currently_played_map_scores();

    draw_player_names(scores);

    draw_player_points(scores);
}

void show_rankings_phase::draw_player_names(
    util::value_ref<std::vector<score_record>> scores) const
{
    auto layout = get_player_names_layout(scores);

    auto const ratio = get_window_fullscreen_ratio().y;

    auto const margin = cinder::Vec2f{150.f, 300.f} * ratio;

    auto const parchment_bounds = get_parchment_bounds();

    auto const top_left = cinder::Vec2f{parchment_bounds.getUL()} + margin;
    
    cinder::gl::draw(layout.render(true, true), top_left);
}

void show_rankings_phase::draw_player_points(
    util::value_ref<std::vector<score_record>> scores) const
{
    auto layout = get_player_points_layout(scores);
    
    auto const ratio = get_window_fullscreen_ratio().y;

    auto const margin = cinder::Vec2f{150.f, 300.f} * ratio;

    auto const parchment_bounds = get_parchment_bounds();

    auto const bottom_right = parchment_bounds.getLR() - margin;

    auto const top_left = cinder::Vec2f{parchment_bounds.getUL()} + margin;

    auto const origin = cinder::Vec2f{bottom_right.x - 75.f * ratio, 
                                      top_left.y};

    cinder::gl::draw(layout.render(true, true), origin);
}

cinder::TextLayout show_rankings_phase::get_player_names_layout(
    util::value_ref<std::vector<score_record>> scores) const
{
    auto const font = get_scores_font();

    auto layout = cinder::TextLayout{};
    
    layout.clear(cinder::ColorA{1.f, 1.f, 1.f, 0.0f});
    layout.setFont(font);
    layout.setColor(cinder::Color{32.f, 0.f, 0.f});

    for (auto const i : util::sequence(0, static_cast<int>(scores.size())))
    {
        layout.addLine(std::to_string(i + 1) + ". " + scores[i].player_name);
    }

    return layout;
}

cinder::TextLayout show_rankings_phase::get_player_points_layout(
    util::value_ref<std::vector<score_record>> scores) const
{
    auto const font = get_scores_font();

    auto layout = cinder::TextLayout{};

    layout.clear(cinder::ColorA{1.f, 1.f, 1.f, 0.0f});
    layout.setFont(font);
    layout.setColor(cinder::Color{32.f, 0.f, 0.f});

    for (auto const i : util::sequence(0, static_cast<int>(scores.size())))
    {
        layout.addRightLine(std::to_string(scores[i].points));
    }

    return layout;
}

cinder::Area show_rankings_phase::get_parchment_bounds() const
{
    auto const parchment_size = get_parchment_size();

    auto const center = cinder::app::getWindowCenter();

    auto const top_left = center - parchment_size * 0.5f;
  
    auto const bottom_right = center + parchment_size * 0.5f;

    return {top_left, bottom_right};
}

cinder::Vec2f show_rankings_phase::get_parchment_size() const
{
    auto const ratio = get_window_fullscreen_ratio();

    return this->parchment_picture.getSize() * 1.5 * ratio.y;
}

cinder::Font show_rankings_phase::get_scores_font() const
{
    auto const ratio = get_window_fullscreen_ratio();

    return {"Arial", 45.f * ratio.y}; 
}

cinder::Vec2f show_rankings_phase::get_window_fullscreen_ratio() const
{
    auto const screen_resolution = get_screen_resolution();

    auto const window_size = cinder::app::getWindowSize();
    
    return {(window_size.x / screen_resolution.x),
            (window_size.y / screen_resolution.y)};
}

void show_rankings_phase::switch_to_playing_phase() const
{
    auto& playing_phase = this->state_machine.get_game_playing_phase();

    this->state_machine.set_current_phase(playing_phase);
}

std::vector<score_record> 
    show_rankings_phase::get_currently_played_map_scores() const
{
    auto& r = get_currently_played_map_rankings();

    return r.get_top_scores(10);
}

high_scores_rankings& 
    show_rankings_phase::get_currently_played_map_rankings() const
{
    auto& phase = this->state_machine.get_map_selection_phase();

    auto& m = phase.get_selected_map();

    auto const map_name = m.get_name();

    return this->rankings.get_rankings_for_map(map_name);
}

}
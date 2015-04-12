#pragma once

#include "snake_overflow/interaction_phase.hpp"
#include "util/value_ref.hpp"
#include <cinder/Text.h>
#include <cinder/gl/Texture.h>
#include <vector>

namespace snake_overflow
{

struct score_record;

class application_state_machine;
class high_scores_database;    
class high_scores_rankings;

class show_rankings_phase : public interaction_phase
{
    
public:

    show_rankings_phase(application_state_machine& state_machine,
                        high_scores_database const& rankings);

    virtual void update() override;

    virtual void draw() override;

    virtual void on_keyboard_input(cinder::app::KeyEvent e) override;

    virtual void on_mouse_down(cinder::app::MouseEvent e) override;

    virtual void on_mouse_drag(cinder::app::MouseEvent e) override;

    virtual void on_mouse_wheel(cinder::app::MouseEvent e) override;

    virtual void on_resize() override;

private:
    
    void load_parchment_image();

    void draw_rankings() const;
    
    void draw_parchment() const;

    void draw_scores() const;

    void draw_player_names(
        util::value_ref<std::vector<score_record>> scores) const;

    void draw_player_points(
        util::value_ref<std::vector<score_record>> scores) const;

    cinder::TextLayout get_player_names_layout(
        util::value_ref<std::vector<score_record>> scores) const;

    cinder::TextLayout get_player_points_layout(
        util::value_ref<std::vector<score_record>> scores) const;

    cinder::Area get_parchment_bounds() const;

    cinder::Vec2f get_parchment_size() const;

    cinder::Font get_scores_font() const;

    cinder::Vec2f get_window_fullscreen_ratio() const;

    void switch_to_playing_phase() const;

    std::vector<score_record> get_currently_played_map_scores() const;

    high_scores_rankings& get_currently_played_map_rankings() const;

private:

    application_state_machine& state_machine;

    high_scores_database const& rankings;

    cinder::gl::Texture parchment_picture;

};

}
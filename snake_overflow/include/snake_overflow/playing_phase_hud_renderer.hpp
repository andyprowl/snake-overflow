#pragma once

#include <cinder/Font.h>

namespace snake_overflow
{

class playing_phase_hud_renderer
{

public:

    playing_phase_hud_renderer();

    void render(int score,
                bool is_game_paused, 
                bool is_game_over,
                bool is_auto_follow_on) const;

private:

    void create_fonts();

    void draw_pause_text() const;

    void draw_score_text(int score) const;

    void draw_game_over_text() const;

    void draw_auto_follow_text() const;

    std::string get_score_text(int const score) const;

private:

    cinder::Font pause_text_font;

    cinder::Font score_text_font;

    cinder::Font game_over_text_font;

    cinder::Font restart_text_font;

    cinder::Font auto_follow_text_font;

};

}
#pragma once

namespace snake_overflow
{

class hud_renderer
{

public:

    hud_renderer();

    void render(float fps,
                int score,
                bool is_game_paused, 
                bool is_game_over,
                bool is_auto_follow_on) const;

    void toogle_show_fps();

private:

    void create_fonts();

    void draw_pause_text() const;

    void draw_fps_text(float fps) const;

    void draw_score_text(int score) const;

    void draw_game_over_text() const;

    void draw_auto_follow_text() const;

    std::string get_fps_text(float fps) const;

    std::string get_score_text(int const score) const;

private:

    cinder::Font fps_text_font;

    cinder::Font pause_text_font;

    cinder::Font score_text_font;

    cinder::Font game_over_text_font;

    cinder::Font auto_follow_text_font;

    bool show_fps;

};

}
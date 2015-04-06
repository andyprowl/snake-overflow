#pragma once

#include <cinder/Font.h>
#include <string>

namespace snake_overflow
{

class application_hud_renderer
{

public:

    application_hud_renderer();

    void render(float fps);

    void toogle_show_fps();

private:

    void create_fonts();

    void draw_fps_text(float fps) const;

    std::string get_fps_text(float fps) const;

private:

    bool show_fps;

    cinder::Font fps_text_font;

};

}
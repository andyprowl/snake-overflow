#pragma once

#include <util/value_ref.hpp>
#include <cinder/Font.h>
#include <string>

namespace snake_overflow
{

class selection_phase_hud_renderer
{

public:

    selection_phase_hud_renderer();

    void render(util::value_ref<std::string> map_name) const;

private:

    void create_fonts();

    void draw_title() const;

    void draw_map_name(util::value_ref<std::string> map_name) const;

private:

    cinder::Font map_name_font;

    cinder::Font title_font;

};

}
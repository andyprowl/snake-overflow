#include "stdafx.hpp"

#include "snake_overflow/application_state_machine.hpp"
#include "snake_overflow/map_selection_phase.hpp"
#include "snake_overflow/player_data_entering_phase.hpp"
#include "util/username.hpp"
#include <cinder/ImageIo.h>
#include <cctype>

namespace snake_overflow
{

static auto const MAX_PLAYER_NAME_LENGTH = 24;

player_data_entering_phase::player_data_entering_phase(
    application_state_machine& state_machine)
    : state_machine{state_machine}
    , player_name(util::get_current_username())
{
    create_fonts();

    load_title_picture();

    load_main_picture();
}

void player_data_entering_phase::update()
{
}

void player_data_entering_phase::draw()
{
    cinder::gl::clear({0.f, 0.f, 0.0f}, true);

    cinder::gl::setMatricesWindow(cinder::app::getWindowSize());

    cinder::gl::enableAlphaBlending();

    draw_main_picture();

    draw_title_picture();

    draw_hint();

    draw_label();

    draw_player_name();

    cinder::gl::disableAlphaBlending();    
}

void player_data_entering_phase::on_keyboard_input(
    cinder::app::KeyEvent const e)
{
    if (e.isControlDown() || e.isAltDown()) { return; }

    if (e.getCode() == cinder::app::KeyEvent::KEY_BACKSPACE)
    {
        auto const length = this->player_name.length();

        this->player_name = this->player_name.substr(0, length - 1);
    }
    else if (e.getCode() == cinder::app::KeyEvent::KEY_RETURN)
    {
        confirm_player_name();
    }

    add_character_to_name_if_valid(e.getChar());
}

void player_data_entering_phase::on_mouse_down(cinder::app::MouseEvent const)
{
}

void player_data_entering_phase::on_mouse_drag(cinder::app::MouseEvent const)
{
}

void player_data_entering_phase::on_mouse_wheel(cinder::app::MouseEvent const)
{
}

void player_data_entering_phase::on_resize()
{
}

std::string player_data_entering_phase::get_player_name() const
{
    return this->player_name;
}

void player_data_entering_phase::create_fonts()
{
    this->title_font = cinder::Font{"Arial", 100.0};

    this->hint_font = cinder::Font{"Arial", 50.0};

    this->max_length_font = cinder::Font{"Arial", 30.0};

    this->label_font = cinder::Font{"Arial", 40.0};

    this->name_font = cinder::Font{"Arial", 40.0};    
}

void player_data_entering_phase::load_title_picture()
{
    auto const asset = cinder::app::loadAsset("images/title.png");

    this->title_picture = cinder::loadImage(asset);
}

void player_data_entering_phase::load_main_picture()
{
    auto const asset = cinder::app::loadAsset("images/snake.png");

    this->main_picture = cinder::loadImage(asset);
}

void player_data_entering_phase::draw_title_picture() const
{
    auto const scaled_title_size = get_scaled_title_size();

    auto const center = cinder::app::getWindowCenter();
    
    auto const top_left = cinder::Vec2f{center.x - scaled_title_size.x / 2,
                                        0.f};

    auto const bottom_right = cinder::Vec2f{center.x + scaled_title_size.x / 2, 
                                            scaled_title_size.y};

    cinder::gl::draw(this->title_picture, {top_left, bottom_right});
}

void player_data_entering_phase::draw_main_picture() const
{
    auto const scaled_title_size = get_scaled_title_size();

    auto const ratio = get_scaling_ratio();

    auto const center = cinder::app::getWindowCenter();

    auto const room_to_center = center.y - scaled_title_size.y;

    auto const picture_size = std::min(room_to_center, 500.f * ratio); 

    auto const top_left = cinder::Vec2f{center.x - picture_size / 2.f, 
                                        scaled_title_size.y + 20};

    auto const bottom_right = cinder::Vec2f{
        center.x + picture_size / 2.f, 
        scaled_title_size.y + 20 + picture_size};

    cinder::gl::draw(this->main_picture, {top_left, bottom_right});
}

void player_data_entering_phase::draw_hint() const
{
    auto const color = cinder::ColorA{0.3f, 1.0f, 0.3f, 1.f};
    
    auto const center = cinder::app::getWindowBounds().getCenter();
    
    auto const origin = cinder::Vec2f{center.x, get_hint_textbox_y()};

    auto const text = "Please choose a name and press 'Enter' to confirm...";

    cinder::gl::drawStringCentered(text, origin, color, this->hint_font);       

    draw_max_length();
}

void player_data_entering_phase::draw_max_length() const
{
    auto const color = cinder::ColorA{0.7f, 0.7f, 0.7f, 1.f};
    
    auto const center = cinder::app::getWindowBounds().getCenter();
    
    auto const origin = cinder::Vec2f{center.x, get_hint_textbox_y() + 50.f};

    auto const formatted_limit = std::to_string(MAX_PLAYER_NAME_LENGTH);

    auto const text = "(maximum length is " + formatted_limit + " characters)";

    cinder::gl::drawStringCentered(text, origin, color, this->max_length_font);       
}

void player_data_entering_phase::draw_label() const
{
    auto const color = cinder::ColorA{1.f, 1.f, 0.f, 1.f};
    
    auto const center = cinder::app::getWindowBounds().getCenter();

    auto const origin = cinder::Vec2f{center.x - 450, 
                                      get_player_name_textbox_y()};

    auto const text = "Player name:";

    cinder::gl::drawString(text, origin, color, this->label_font);    
}

void player_data_entering_phase::draw_player_name() const
{
    auto const color = cinder::ColorA{1.f, 1.f, 1.f, 1.f};
    
    auto const center = cinder::app::getWindowBounds().getCenter();

    auto const origin = cinder::Vec2f{center.x - 250.f, 
                                      get_player_name_textbox_y()};

    auto const seconds = static_cast<int>(cinder::app::getElapsedSeconds());

    auto const name = this->player_name + ((seconds % 2) ? "_" : "");

    cinder::gl::drawString(name, origin, color, this->name_font);
}

cinder::Vec2f player_data_entering_phase::get_scaled_title_size() const
{
    auto const title_size = cinder::Vec2f{this->title_picture.getSize()};

    auto const ratio = get_scaling_ratio();

    return (title_size * ratio); 
}

float player_data_entering_phase::get_scaling_ratio() const
{
    auto const title_size = cinder::Vec2f{this->title_picture.getSize()};

    auto const window_size = cinder::app::getWindowSize();

    return (window_size.x / title_size.x);
}

float player_data_entering_phase::get_hint_textbox_y() const
{
    auto const window_size = cinder::app::getWindowSize();

    return (window_size.y * 0.6f);
}

float player_data_entering_phase::get_player_name_textbox_y() const
{
    return (get_hint_textbox_y() + 100.f);
}

void player_data_entering_phase::add_character_to_name_if_valid(char const c)
{
    if (this->player_name.length() >= MAX_PLAYER_NAME_LENGTH)
    {
        return;
    }

    if (is_valid_name_character(c))
    {
        this->player_name += c;
    }    
}

bool player_data_entering_phase::is_valid_name_character(char const c) const
{
    return (std::isalpha(c) || (std::isdigit(c)) || (c == ' '));
}

void player_data_entering_phase::confirm_player_name()
{
    if (this->player_name.empty())
    {
        return;
    }

    switch_to_map_selection_phase();
}

void player_data_entering_phase::switch_to_map_selection_phase()
{
    auto& next_phase = this->state_machine.get_map_selection_phase();

    this->state_machine.set_current_phase(next_phase);
}

}
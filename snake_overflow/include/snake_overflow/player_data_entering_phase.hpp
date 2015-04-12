#pragma once

#include "snake_overflow/interaction_phase.hpp"
#include <cinder/Font.h>
#include <cinder/gl/Texture.h>
#include <string>

namespace snake_overflow
{

class application_state_machine;
    
class player_data_entering_phase : public interaction_phase
{

public:

    player_data_entering_phase(application_state_machine& state_machine);
    
    virtual void update() override;
    
    virtual void draw() override;
    
    virtual void on_keyboard_input(cinder::app::KeyEvent e) override;
    
    virtual void on_mouse_down(cinder::app::MouseEvent e) override;
    
    virtual void on_mouse_drag(cinder::app::MouseEvent e) override; 
    
    virtual void on_mouse_wheel(cinder::app::MouseEvent e) override;
    
    virtual void on_resize() override;

    std::string get_player_name() const;

private:

    void create_fonts();

    void load_title_picture();

    void load_main_picture();

    void draw_title_picture() const;

    void draw_main_picture() const;

    void draw_hint() const;

    void draw_max_length() const;

    void draw_label() const;

    void draw_player_name() const;

    cinder::Vec2f get_scaled_title_size() const;

    float get_scaling_ratio() const;

    float get_hint_textbox_y() const;

    float get_player_name_textbox_y() const;

    void add_character_to_name_if_valid(char c);

    bool is_valid_name_character(char c) const;

    void confirm_player_name();

    void switch_to_map_selection_phase();

private:

    application_state_machine& state_machine;

    std::string player_name;

    cinder::Font title_font;

    cinder::Font hint_font;

    cinder::Font max_length_font;

    cinder::Font label_font;

    cinder::Font name_font;

    cinder::gl::Texture title_picture;

    cinder::gl::Texture main_picture;

};

}
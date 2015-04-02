#include "stdafx.hpp"

#include "snake_overflow/camera_manipulator.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/hud_renderer.hpp"
#include "snake_overflow/keyboard_input_handler.hpp"

namespace snake_overflow
{

keyboard_input_handler::keyboard_input_handler(
    game& controlled_game, 
    hud_renderer& hud_drawer,
    camera_manipulator& camera_handler)
    : controlled_game{controlled_game}
    , hud_drawer{hud_drawer}
    , camera_handler{camera_handler}
{
    setup_keyboard_commands();
}

void keyboard_input_handler::process_keyboard_input(int const code)
{
    auto it = this->keyboard_commands.find(code);
    
    if (it != std::cend(this->keyboard_commands))
    {
        try
        {
            (it->second)();
        }
        catch (std::exception const&)
        {
        }
    }
}

void keyboard_input_handler::setup_keyboard_commands()
{
    setup_action_commands();

    setup_camera_commands();

    setup_option_commands();
}

void keyboard_input_handler::setup_action_commands()
{
    using cinder::app::KeyEvent;

    auto turn_left_cmd = [this] { turn_snake_left(); };
    
    this->keyboard_commands[KeyEvent::KEY_a] = turn_left_cmd;
    this->keyboard_commands[KeyEvent::KEY_LEFT] = turn_left_cmd;

    auto turn_right_cmd = [this] { turn_snake_right(); };
    
    this->keyboard_commands[KeyEvent::KEY_d] = turn_right_cmd;
    this->keyboard_commands[KeyEvent::KEY_RIGHT] = turn_right_cmd;
}

void keyboard_input_handler::setup_camera_commands()
{
    using cinder::app::KeyEvent;
    
    this->keyboard_commands[KeyEvent::KEY_w] = [this] 
    { 
        this->camera_handler.zoom(1.f);
    };
    
    this->keyboard_commands[KeyEvent::KEY_s] = [this] 
    { 
        this->camera_handler.zoom(-1.f);
    };

    this->keyboard_commands[KeyEvent::KEY_SPACE] = [this] 
    { 
        this->camera_handler.toggle_auto_follow(); 
    };
}

void keyboard_input_handler::setup_option_commands()
{
    using cinder::app::KeyEvent;

    this->keyboard_commands[KeyEvent::KEY_p] = [this] 
    { 
        this->controlled_game.toggle_game_pause();
    };

    this->keyboard_commands[KeyEvent::KEY_f] = [this] 
    { 
        this->hud_drawer.toogle_show_fps(); 
    };
}

void keyboard_input_handler::turn_snake_left() const
{
    auto& s = this->controlled_game.get_snake();

    return s.turn_left();
}

void keyboard_input_handler::turn_snake_right() const
{
    auto& s = this->controlled_game.get_snake();

    return s.turn_right();
}

}
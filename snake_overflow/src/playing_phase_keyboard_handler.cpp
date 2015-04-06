#include "stdafx.hpp"

#include "snake_overflow/camera_manipulator.hpp"
#include "snake_overflow/camera_manipulator_toggler.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/game_over_continuation_option.hpp"
#include "snake_overflow/playing_phase_hud_renderer.hpp"
#include "snake_overflow/playing_phase_keyboard_handler.hpp"

namespace snake_overflow
{

playing_phase_keyboard_handler::playing_phase_keyboard_handler(
    game& controlled_game, 
    playing_phase_hud_renderer& hud_drawer,
    camera_manipulator_toggler& camera_toggler,
    continuation_option_setter& option_setter)
    : controlled_game{controlled_game}
    , hud_drawer{hud_drawer}
    , camera_toggler{camera_toggler}
    , option_setter{option_setter}
{
    setup_keyboard_commands();
}

void playing_phase_keyboard_handler::process_keyboard_input(int const code)
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

void playing_phase_keyboard_handler::setup_keyboard_commands()
{
    setup_action_commands();

    setup_camera_commands();

    setup_option_commands();
}

void playing_phase_keyboard_handler::setup_action_commands()
{
    using cinder::app::KeyEvent;

    auto turn_left_cmd = [this] { turn_snake_left(); };
    
    this->keyboard_commands[KeyEvent::KEY_a] = turn_left_cmd;
    this->keyboard_commands[KeyEvent::KEY_LEFT] = turn_left_cmd;

    auto turn_right_cmd = [this] { turn_snake_right(); };
    
    this->keyboard_commands[KeyEvent::KEY_d] = turn_right_cmd;
    this->keyboard_commands[KeyEvent::KEY_RIGHT] = turn_right_cmd;

    this->keyboard_commands[KeyEvent::KEY_i] = [this]
    {
        this->controlled_game.get_snake().invulnerability_bonus = true;
    };
}

void playing_phase_keyboard_handler::setup_camera_commands()
{
    using cinder::app::KeyEvent;
    
    this->keyboard_commands[KeyEvent::KEY_w] = [this] 
    { 
        this->camera_toggler.get_current_manipulator().zoom(1.f);
    };
    
    this->keyboard_commands[KeyEvent::KEY_s] = [this] 
    { 
        this->camera_toggler.get_current_manipulator().zoom(-1.f);
    };

    this->keyboard_commands[KeyEvent::KEY_SPACE] = [this] 
    { 
        this->camera_toggler.activate_next_camera_manipulator(); 
    };
}

void playing_phase_keyboard_handler::setup_option_commands()
{
    using cinder::app::KeyEvent;

    this->keyboard_commands[KeyEvent::KEY_p] = [this] 
    { 
        toggle_game_pause(this->controlled_game);
    };

    auto const restart_cmd = [this]
    {
        this->option_setter.set_continuation_option(
            game_over_continuation_option::restart_game);
    };

    this->keyboard_commands[KeyEvent::KEY_F5] = restart_cmd;
    this->keyboard_commands[KeyEvent::KEY_RETURN] = restart_cmd;

    this->keyboard_commands[KeyEvent::KEY_F4] = [this]
    {
        this->option_setter.set_continuation_option(
            game_over_continuation_option::change_map);
    };
}

void playing_phase_keyboard_handler::turn_snake_left() const
{
    auto& s = this->controlled_game.get_snake();

    return s.turn_left();
}

void playing_phase_keyboard_handler::turn_snake_right() const
{
    auto& s = this->controlled_game.get_snake();

    return s.turn_right();
}

}
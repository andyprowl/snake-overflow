#include "stdafx.hpp"

#include "snake_overflow/application_state_machine.hpp"
#include "snake_overflow/camera_manipulator.hpp"
#include "snake_overflow/camera_manipulator_toggler.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/game_playing_phase.hpp"
#include "snake_overflow/map_selection_phase.hpp"
#include "snake_overflow/playing_phase_hud_renderer.hpp"
#include "snake_overflow/playing_phase_keyboard_handler.hpp"
#include "snake_overflow/show_rankings_phase.hpp"

namespace snake_overflow
{

playing_phase_keyboard_handler::playing_phase_keyboard_handler(
    application_state_machine& state_machine,
    game& controlled_game, 
    playing_phase_hud_renderer& hud_drawer,
    camera_manipulator_toggler& camera_toggler)
    : state_machine{state_machine}
    , controlled_game{controlled_game}
    , hud_drawer{hud_drawer}
    , camera_toggler{camera_toggler}
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
        start_new_game_on_same_map();
    };

    this->keyboard_commands[KeyEvent::KEY_F5] = restart_cmd;
    this->keyboard_commands[KeyEvent::KEY_RETURN] = restart_cmd;

    this->keyboard_commands[KeyEvent::KEY_F4] = [this]
    {
        switch_to_map_selection_phase();
    };

    this->keyboard_commands[KeyEvent::KEY_r] = [this]
    {
        switch_to_show_rankings_phase();
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

void playing_phase_keyboard_handler::start_new_game_on_same_map() const
{
    auto& playing_phase = this->state_machine.get_game_playing_phase();

    this->state_machine.set_current_phase(playing_phase);

    restart_game_and_destroy_self();
}

void playing_phase_keyboard_handler::switch_to_map_selection_phase() const
{
    auto& selection_phase =this->state_machine.get_map_selection_phase();

    this->state_machine.set_current_phase(selection_phase);
}

void playing_phase_keyboard_handler::switch_to_show_rankings_phase() const
{ 
    auto& rankings_phase = this->state_machine.get_show_rankings_phase();

    this->state_machine.set_current_phase(rankings_phase);
}

void playing_phase_keyboard_handler::restart_game_and_destroy_self() const
{
    auto& playing_phase = this->state_machine.get_game_playing_phase();

    // This indirectly causes self-destruction!
    playing_phase.restart_game();
}

}
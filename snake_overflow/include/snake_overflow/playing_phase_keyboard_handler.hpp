#pragma once

#include <functional>
#include <unordered_map>

namespace snake_overflow
{

class camera_manipulator_toggler;
class continuation_option_setter;
class game;
class playing_phase_hud_renderer;

class playing_phase_keyboard_handler
{

public:

    playing_phase_keyboard_handler(game& controlled_game, 
                                   playing_phase_hud_renderer& hud_drawer,
                                   camera_manipulator_toggler& camera_toggler,
                                   continuation_option_setter& option_setter);

    void process_keyboard_input(int const code);

private:

    void setup_keyboard_commands();

    void setup_action_commands();

    void setup_camera_commands();

    void setup_option_commands();

    void turn_snake_left() const;

    void turn_snake_right() const;

private:

    game& controlled_game;

    playing_phase_hud_renderer& hud_drawer;

    camera_manipulator_toggler& camera_toggler;

    continuation_option_setter& option_setter;

    std::unordered_map<int, std::function<void()>> keyboard_commands;

};

}
#pragma once

#include <functional>
#include <unordered_map>

namespace snake_overflow
{

class application_state_machine;
class camera_manipulator_toggler;
class game;
class playing_phase_hud_renderer;

class playing_phase_keyboard_handler
{

public:

    playing_phase_keyboard_handler(application_state_machine& state_machine,
                                   game& controlled_game, 
                                   playing_phase_hud_renderer& hud_drawer,
                                   camera_manipulator_toggler& camera_toggler);

    void process_keyboard_input(int const code);

private:

    void setup_keyboard_commands();

    void setup_action_commands();

    void setup_camera_commands();

    void setup_option_commands();

    void turn_snake_left() const;

    void turn_snake_right() const;

    void start_new_game_on_same_map() const;

    void switch_to_map_selection_phase() const;

    void restart_game_and_destroy_self() const;

private:

    application_state_machine& state_machine;

    game& controlled_game;

    playing_phase_hud_renderer& hud_drawer;

    camera_manipulator_toggler& camera_toggler;

    std::unordered_map<int, std::function<void()>> keyboard_commands;

};

}
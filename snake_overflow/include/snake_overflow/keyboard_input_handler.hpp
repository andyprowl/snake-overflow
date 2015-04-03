#pragma once

#include <functional>
#include <unordered_map>

namespace snake_overflow
{

class game;
class hud_renderer;

class keyboard_input_handler
{

public:

    keyboard_input_handler(game& controlled_game, 
                           hud_renderer& hud_drawer, 
                           camera_manipulator& camera_handler);

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

    hud_renderer& hud_drawer;

    camera_manipulator& camera_handler;

    std::unordered_map<int, std::function<void()>> keyboard_commands;

};

}
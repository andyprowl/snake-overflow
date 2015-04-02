#pragma once

#include "snake_overflow/game.hpp"
#include "snake_overflow/texture_repository.hpp"
#include "cinder/Arcball.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

namespace snake_overflow
{

struct camera_view;

class hud_renderer;
class random_item_position_picker;
class snake;
class world_renderer;

class application : public cinder::app::AppNative 
{
 
public:
    
    virtual void prepareSettings(Settings* settings) override;

    virtual void setup() override;
        
    virtual void update() override;
    
    virtual void draw() override;

    virtual void keyDown(cinder::app::KeyEvent e) override;

    virtual void mouseDown(cinder::app::MouseEvent e) override;

    virtual void mouseDrag(cinder::app::MouseEvent e) override;

    virtual void mouseWheel(cinder::app::MouseEvent e) override;

private:

    void create_game();

    void spawn_items();

    void populate_habitat(terrain& habitat);
        
    void create_renderers();

    void create_world_renderer();

    void create_hud_renderer();

    void setup_perspective_camera();

    camera_view get_camera_view() const;

    camera_view get_auto_follow_camera_view() const;

    void setup_arcball_manipulator();

    void setup_depth_buffer();

    void setup_keyboard_commands();

    void setup_action_commands();

    void setup_camera_commands();

    void setup_option_commands();

    void draw_frame();

    void draw_world();

    int get_zoom_step() const;

    void calculate_current_fps();

    void turn_snake_left() const;

    void turn_snake_right() const;

private:

    std::unique_ptr<game> current_game;
        
    std::unique_ptr<texture_repository> textures;

    std::unique_ptr<world_renderer> world_drawer;

    std::unique_ptr<hud_renderer> hud_drawer;

    int cube_side_length = 20;

    float block_size = 20.f;

    cinder::CameraPersp camera;
    
    float camera_distance = 600.f;

    cinder::Arcball arcball;

    bool auto_follow = false;

    std::chrono::time_point<std::chrono::system_clock> last_frame_time;

    float current_fps = 60.0;

    std::unordered_map<int, std::function<void()>> keyboard_commands;

};

}
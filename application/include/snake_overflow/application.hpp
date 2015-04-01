#pragma once

#include "snake_overflow/game.hpp"
#include "snake_overflow/item_renderer.hpp"
#include "snake_overflow/terrain_renderer.hpp"
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

class random_item_position_picker;
class snake;
class snake_renderer;

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

    void populate_habitat();

    void create_texture_repository();

    void create_renderers();

    void create_snake_renderer();

    void create_item_renderer();

    void create_terrain_renderer();

    void setup_perspective_camera();

    void setup_arcball_manipulator();

    void setup_depth_buffer();

    void create_fonts();

    void setup_keyboard_commands();

    void setup_action_commands();

    void setup_camera_commands();

    void setup_option_commands();

    void draw_frame();

    int get_zoom_step() const;

    void calculate_current_fps();

    void draw_pause_text() const;

    void draw_fps_text() const;

    void draw_score_text() const;

    std::string get_current_fps_text() const;

    std::string get_score_text() const;

    void turn_snake_left() const;

    void turn_snake_right() const;

private:

    std::unique_ptr<game> current_game;
        
    int cube_side_length = 20;

    float block_size = 20.f;

    std::unique_ptr<texture_repository> textures;

    std::unique_ptr<snake_renderer> hero_drawer;

    std::unique_ptr<item_renderer> item_drawer;

    std::unique_ptr<terrain_renderer> habitat_drawer;

    cinder::CameraPersp camera;
    
    float camera_distance = 550.f;

    cinder::Arcball arcball;

    bool paused = false;

    bool show_fps = false;

    std::chrono::time_point<std::chrono::system_clock> last_frame_time;

    float current_fps = 60.0;

    cinder::Font fps_text_font;

    cinder::Font pause_text_font;

    cinder::Font score_text_font;

    std::unordered_map<int, std::function<void()>> keyboard_commands;

};

}
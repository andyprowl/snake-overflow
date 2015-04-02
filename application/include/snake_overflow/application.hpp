#pragma once

#include <chrono>
#include <memory>

namespace snake_overflow
{

class camera_manipulator;
class game;
class hud_renderer;
class keyboard_input_handler;
class terrain;
class terrain_provider;
class texture_repository;
class world_renderer;

class application : public cinder::app::AppNative 
{
 
private:
    
    virtual void prepareSettings(Settings* settings) override;

    virtual void setup() override;
        
    virtual void update() override;
    
    virtual void draw() override;

    virtual void keyDown(cinder::app::KeyEvent e) override;

    virtual void mouseDown(cinder::app::MouseEvent e) override;

    virtual void mouseDrag(cinder::app::MouseEvent e) override;

    virtual void mouseWheel(cinder::app::MouseEvent e) override;

    void create_terrain_provider();

    void create_game();

    void create_renderers();

    void create_world_renderer();

    void create_hud_renderer();

    void create_camera_manipulator();

    void create_keyboard_input_handler();

    void setup_depth_buffer();

    void draw_frame();

    void draw_world();

    void calculate_current_fps();

private:

    std::unique_ptr<game> current_game;
        
    std::unique_ptr<terrain_provider> habitat_provider;

    std::unique_ptr<texture_repository> textures;

    std::unique_ptr<world_renderer> world_drawer;

    std::unique_ptr<hud_renderer> hud_drawer;

    std::unique_ptr<camera_manipulator> camera_handler;

    std::unique_ptr<keyboard_input_handler> keyboard_handler;

    float block_size = 20.f;

    std::chrono::time_point<std::chrono::system_clock> last_frame_time;

    float current_fps = 60.0;

};

}
#pragma once

#include "snake_overflow/snake_renderer.hpp"
#include "snake_overflow/territory.hpp"
#include "snake_overflow/territory_renderer.hpp"
#include "cinder/Arcball.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include <memory>

namespace snake_overflow
{

class snake;

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

private:

    void create_habitat();

    void create_snake();

    void setup_perspective_camera();

    void setup_arcball_manipulator();

    void setup_gui_control_parameters();

    void setup_depth_buffer();

    void draw_game();

private:

    territory habitat;

    std::unique_ptr<snake> hero;

    int cube_side_length = 16;

    float block_size = 15.f;

    float snake_height = 5.f;

    float snake_width = block_size / 3;

    territory_renderer habitat_renderer{block_size};

    snake_renderer hero_renderer{snake_width, snake_height, block_size};

    cinder::CameraPersp camera;

    cinder::params::InterfaceGlRef parameters;

    float camera_distance = 500.f;

    cinder::Arcball arcball;

    bool paused = false;

};

}
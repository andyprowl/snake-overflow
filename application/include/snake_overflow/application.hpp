#pragma once

#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_renderer.hpp"
#include "snake_overflow/texture_repository.hpp"
#include "cinder/Arcball.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include <memory>

namespace snake_overflow
{

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

    void create_habitat();

    void create_snake();

    void create_texture_repository();

    void create_renderers();

    void create_snake_renderer();

    void create_terrain_renderer();

    void setup_perspective_camera();

    void setup_arcball_manipulator();

    void setup_depth_buffer();

    void draw_frame();

    int get_zoom_step() const;

private:

    terrain habitat;

    std::unique_ptr<snake> hero;
    
    int cube_side_length = 20;

    float block_size = 25.f;

    std::unique_ptr<texture_repository> textures;

    std::unique_ptr<terrain_renderer> habitat_renderer;

    std::unique_ptr<snake_renderer> hero_renderer;

    cinder::CameraPersp camera;
    
    float camera_distance = 650.f;

    cinder::Arcball arcball;

    bool paused = false;

};

}
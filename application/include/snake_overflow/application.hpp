#pragma once

#include "snake_overflow/snake_renderer.hpp"
#include "snake_overflow/territory.hpp"
#include "snake_overflow/territory_renderer.hpp"
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

private:

    void create_snake();

    void setup_parameters();

private:

    territory habitat;

    std::unique_ptr<snake> hero;

    float block_size = 15.f;

    float snake_height = 3.f;

    territory_renderer habitat_renderer{block_size};

    snake_renderer hero_renderer{block_size / 2.f, snake_height, block_size};

    cinder::CameraPersp camera;

    cinder::params::InterfaceGlRef parameters;

    cinder::Quatf camera_rotation;

    float camera_distance = 500.f;

};

}
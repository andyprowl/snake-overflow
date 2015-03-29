#pragma once

#include "snake_overflow/territory.hpp"
#include "snake_overflow/territory_renderer.hpp"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"

namespace snake_overflow
{

class application : public cinder::app::AppNative 
{
 
public:
    
    virtual void prepareSettings(Settings* settings) override;

    virtual void setup() override;
        
    virtual void update() override;
    
    virtual void draw() override;

private:

    void setup_parameters();

private:

    territory habitat;

    territory_renderer renderer{15.f};

    cinder::CameraPersp camera;

    cinder::params::InterfaceGlRef parameters;

    cinder::Quatf camera_rotation;

    float camera_distance = 500.f;

};

}
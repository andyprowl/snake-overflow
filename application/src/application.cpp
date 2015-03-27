#include "stdafx.hpp"

namespace snake_overflow
{

class application : public cinder::app::AppNative 
{
 
public:
    
    virtual void prepareSettings(Settings* settings) override;

    virtual void setup() override;
        
    virtual void update() override;
    
    virtual void draw() override;
};

void application::setup()
{
}

void application::prepareSettings(Settings* settings)
{
    settings->setWindowSize(800, 600);
    settings->setFrameRate(60);
}

void application::update()
{
}

void application::draw()
{
}

}

CINDER_APP_NATIVE(snake_overflow::application, ci::app::RendererGl)

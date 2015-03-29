#include "stdafx.hpp"

#include "snake_overflow/application.hpp"
#include "snake_overflow/cube_builder.hpp"

namespace snake_overflow
{

void application::setup()
{
    auto builder = cube_builder{this->habitat};

    builder.add_cube({0, 0, 0}, 10);

    this->camera.setPerspective(60.0f, getWindowAspectRatio(), 5.0f, 3000.0f);

    setup_parameters();
}

void application::prepareSettings(Settings* const settings)
{
    settings->setWindowSize(800, 600);

    settings->setFrameRate(60);
}

void application::update()
{
    auto const eye = cinder::Vec3f{0.0f, 0.0f, this->camera_distance};
    auto const center = cinder::Vec3f::zero();
    auto const up = cinder::Vec3f::zAxis();

    this->camera.lookAt(eye, center, up);
    cinder::gl::setMatrices(this->camera);
    cinder::gl::rotate(this->camera_rotation);
}

void application::draw()
{
    cinder::gl::clear({0.f, 0.f, 0.0f}, true);
    cinder::gl::enableDepthRead();
    cinder::gl::enableDepthWrite();

    this->parameters->draw();

    this->renderer.render(this->habitat);
}

void application::setup_parameters()
{
    this->parameters = cinder::params::InterfaceGl::create("Snake", {200, 160});
    
    this->parameters->addParam("Scene Rotation", 
                               &this->camera_rotation, 
                               "opened=1");
    
    this->parameters->addSeparator();
    
    this->parameters->addParam(
        "Eye Distance", 
        &this->camera_distance, 
        "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w");
}

}

CINDER_APP_NATIVE(snake_overflow::application, ci::app::RendererGl)

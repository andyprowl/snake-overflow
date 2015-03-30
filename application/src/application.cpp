#include "stdafx.hpp"

#include "snake_overflow/application.hpp"
#include "snake_overflow/cube_builder.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/snake.hpp"
#include "util/repeat.hpp"

namespace snake_overflow
{

void application::setup()
{
    create_habitat();

    create_snake();

    setup_gui_control_parameters();

    setup_arcball_manipulator();

    setup_depth_buffer();
}

void application::prepareSettings(Settings* const settings)
{
    settings->setWindowSize(800, 600);

    settings->setFrameRate(60);
}

void application::update()
{
    if ((getElapsedFrames() % 10 == 0) && !(this->paused))
    {
        this->hero->advance();
    }
}

void application::draw()
{
    setup_perspective_camera();

    cinder::gl::rotate(this->arcball.getQuat());

    cinder::gl::rotate(cinder::Quatf{cinder::Vec3f::xAxis(), 1.57f});

    cinder::gl::rotate(cinder::Quatf{cinder::Vec3f::yAxis(), 3.14f});
    
    cinder::gl::clear({0.f, 0.f, 0.0f}, true);

    this->parameters->draw();

    draw_game();
}

void application::keyDown(cinder::app::KeyEvent const e)
{
    switch (e.getCode())
    {
        case cinder::app::KeyEvent::KEY_LEFT:
        {
            return this->hero->turn_left();
        }

        case cinder::app::KeyEvent::KEY_RIGHT:
        {
            return this->hero->turn_right();
        }

        case cinder::app::KeyEvent::KEY_p:
        {
            this->paused = !(this->paused);
            return;
        }

        default:
        {
        }
    }
}

void application::mouseDown(cinder::app::MouseEvent const e)
{
    this->arcball.mouseDown(e.getPos());
}

void application::mouseDrag(cinder::app::MouseEvent const e)
{
    this->arcball.mouseDrag(e.getPos());
}

void application::create_habitat()
{
    auto builder = cube_builder{this->habitat};

    builder.add_centered_cube({0, 0, 0}, cube_side_length);
}

void application::create_snake()
{
    auto const initial_state = dynamics{{0, -8, -8}, 
                                        {block_face::front, 
                                        canonical_direction::positive_z()}};

    this->hero = std::make_unique<snake>(this->habitat, initial_state, 5);
}

void application::setup_perspective_camera()
{
    auto const eye = cinder::Vec3f{0.f, 0.f, -this->camera_distance};
    auto const center = cinder::Vec3f::zero();
    auto const up = cinder::Vec3f::yAxis();

    this->camera.setPerspective(60.0f, getWindowAspectRatio(), 5.f, 3000.f);
    this->camera.lookAt(eye, center, up);
    cinder::gl::setMatrices(this->camera);
}

void application::setup_arcball_manipulator()
{
    this->arcball.setWindowSize(getWindowSize());

    this->arcball.setCenter(getWindowCenter());
    
    this->arcball.setRadius(150);
}

void application::setup_gui_control_parameters()
{
    this->parameters = cinder::params::InterfaceGl::create("Snake", {200, 25});

    this->parameters->addParam(
        "Eye Distance", 
        &this->camera_distance, 
        "min=50.0 max=1500.0 step=50.0 keyIncr=s keyDecr=w");
}

void application::setup_depth_buffer()
{
    cinder::gl::enableDepthRead();
    
    cinder::gl::enableDepthWrite();
}

void application::draw_game()
{
    this->habitat_renderer.render(this->habitat);

    this->hero_renderer.render(*this->hero);
}

}

CINDER_APP_NATIVE(snake_overflow::application, ci::app::RendererGl)

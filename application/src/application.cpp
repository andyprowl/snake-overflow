#include "stdafx.hpp"

#include "snake_overflow/application.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/snake_renderer.hpp"
#include "cinder/ImageIo.h"
#include "util/repeat.hpp"

namespace snake_overflow
{

void application::setup()
{
    create_habitat();

    create_snake();

    create_renderers();
    
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
    if ((getElapsedFrames() % 5 == 0) && !(this->paused))
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
    
    draw_frame();
}

void application::keyDown(cinder::app::KeyEvent const e)
{
    switch (e.getCode())
    {
        case cinder::app::KeyEvent::KEY_a:
        case cinder::app::KeyEvent::KEY_LEFT:
        {
            return this->hero->turn_left();
        }

        case cinder::app::KeyEvent::KEY_d:
        case cinder::app::KeyEvent::KEY_RIGHT:
        {
            return this->hero->turn_right();
        }

        case cinder::app::KeyEvent::KEY_w:
        {
            this->camera_distance -= get_zoom_step();
            return;
        }

        case cinder::app::KeyEvent::KEY_s:
        {
            this->camera_distance += get_zoom_step();
            return;
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

void application::mouseWheel(cinder::app::MouseEvent const e)
{
    this->camera_distance -= e.getWheelIncrement() * get_zoom_step();
}

void application::create_habitat()
{
    auto builder = terrain_builder{this->habitat};

    builder.add_centered_cube({0, 0, 0}, 
                              this->cube_side_length, 
                              "grass4.jpg",
                              {255, 255, 255, 255},
                              true);

    builder.add_cuboid({this->cube_side_length / 2, 
                        this->cube_side_length / 4, 
                        this->cube_side_length / 4}, 
                       {this->cube_side_length / 4, 5, 3},
                       "water2.jpg",
                       {255, 255, 255, 100},
                       false);

    builder.add_cuboid({-this->cube_side_length / 2, 
                        -this->cube_side_length / 4, 
                        this->cube_side_length / 4 + 4}, 
                       {7, 6, 4}, 
                       "lava5.jpg",
                       {255, 255, 255, 255},
                       true);

    builder.add_cube({0, -this->cube_side_length / 2 - 7, 0}, 
                     7, 
                     "stone3.jpg",
                     {255, 255, 255, 255},
                     true);
}

void application::create_snake()
{
    auto const snake_origin = point{0, 
                                    -this->cube_side_length / 2, 
                                    -this->cube_side_length / 2};

    auto const initial_state = dynamics{snake_origin, 
                                        {block_face::front, 
                                        canonical_direction::positive_z()}};

    this->hero = std::make_unique<snake>(this->habitat, initial_state, 25);
}

void application::create_texture_repository()
{
    this->textures = std::make_unique<texture_repository>();
}

void application::create_renderers()
{
    create_texture_repository();
    
    create_snake_renderer();

    create_terrain_renderer();
}

void application::create_snake_renderer()
{
    float snake_height = 8.f;

    float snake_width = this->block_size / 2;

    auto const skin = this->textures->get_texture("snake7.jpg");

    this->hero_renderer = std::make_unique<snake_renderer>(snake_width, 
                                                           snake_height, 
                                                           this->block_size,
                                                           skin);
}

void application::create_terrain_renderer()
{
    this->habitat_renderer = std::make_unique<terrain_renderer>(
        this->block_size, 
        *this->textures);
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

void application::setup_depth_buffer()
{
    cinder::gl::enableDepthRead();
    
    cinder::gl::enableDepthWrite();
}

void application::draw_frame()
{
    this->hero_renderer->render(*this->hero);

    this->habitat_renderer->render(this->habitat);
}

int application::get_zoom_step() const
{
    return 20;
}

}

CINDER_APP_NATIVE(snake_overflow::application, ci::app::RendererGl)

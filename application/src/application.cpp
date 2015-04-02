#include "stdafx.hpp"

#include "snake_overflow/application.hpp"
#include "snake_overflow/camera_view.hpp"
#include "snake_overflow/hud_renderer.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/random_item_position_picker.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/snake_renderer.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/world_renderer.hpp"
#include "cinder/ImageIo.h"
#include "util/repeat.hpp"
#include <unordered_set>


#include "snake_overflow/fruit.hpp"
#include <memory>


namespace snake_overflow
{

void application::setup()
{
    create_game();

    spawn_items();

    create_renderers();

    setup_arcball_manipulator();

    setup_depth_buffer();

    setup_keyboard_commands();

    this->last_frame_time = std::chrono::system_clock::now();
}

void application::prepareSettings(Settings* const settings)
{
    settings->setWindowSize(1024, 768);

    settings->setFrameRate(30);
}

void application::update()
{
    auto const game_over = this->current_game->is_game_over();

    if ((getElapsedFrames() % 3 == 0) && !game_over)
    {
        this->current_game->update();
    }
}

void application::draw()
{
    setup_perspective_camera();

    if (!this->auto_follow)
    {
        cinder::gl::rotate(this->arcball.getQuat());
    }
    
    cinder::gl::clear({0.f, 0.f, 0.0f}, true);
    
    draw_frame();
}

void application::keyDown(cinder::app::KeyEvent const e)
{
    auto it = this->keyboard_commands.find(e.getCode());
    
    if (it != std::cend(this->keyboard_commands))
    {
        try
        {
            (it->second)();
        }
        catch (std::exception const&)
        {
        }
    }
}

void application::mouseDown(cinder::app::MouseEvent const e)
{
    auto const pos = e.getPos();

    auto const bottom = static_cast<int>(getWindowBounds().getLR().y);

    this->arcball.mouseDown({pos.x, bottom - pos.y});
}

void application::mouseDrag(cinder::app::MouseEvent const e)
{
    auto const pos = e.getPos();

    auto const bottom = static_cast<int>(getWindowBounds().getLR().y);

    this->arcball.mouseDrag({pos.x, bottom - pos.y});
}

void application::mouseWheel(cinder::app::MouseEvent const e)
{
    this->camera_distance -= e.getWheelIncrement() * get_zoom_step();
}

void application::create_game()
{
    auto habitat = std::make_unique<terrain>();

    populate_habitat(*habitat);

    auto const snake_origin = point{0, 
                                    -5, 
                                    this->cube_side_length / 2};

    auto const initial_step = footprint{snake_origin, 
                                        {block_face::top, 
                                        canonical_direction::positive_y()}};

    auto s = std::make_unique<snake>(*habitat, initial_step, 5);

    this->current_game = std::make_unique<game>(std::move(habitat), 
                                                std::move(s));
}

void application::populate_habitat(terrain& habitat)
{
    auto builder = terrain_builder{habitat};

    builder.add_centered_cube({0, 0, 0}, 
                              this->cube_side_length, 
                              "grass4.jpg",
                              {255, 255, 255, 255},
                              true);

    auto const pool_sizes = point{7, 9, 3};

    auto const pool_origin = point{this->cube_side_length / 2,
                                   this->cube_side_length / 2 - pool_sizes.y,
                                   this->cube_side_length / 4};

    builder.add_box(pool_origin,
                    pool_sizes,
                    "brick1.jpg",
                    {255, 255, 255, 255},
                    true);

    builder.remove_box(pool_origin + point{1, 1, 1},
                       pool_sizes - point{2, 2, 1});

    builder.add_box(pool_origin + point{1, 1, 1}, 
                    pool_sizes - point{2, 2, 1},
                    "water4.jpg",
                    {255, 255, 255, 100},
                     false);

    builder.add_box({-this->cube_side_length / 2, 
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

    builder.add_cube({0, 0, this->cube_side_length / 2}, 
                     1, 
                     "stone3.jpg",
                     {255, 255, 255, 255},
                     true);
}

void application::spawn_items()
{
    auto& habitat = this->current_game->get_terrain();

    auto const picker = random_item_position_picker{habitat};

    auto num_of_spawned_items = 0;
    while (num_of_spawned_items < 30)
    {
        try
        {
            auto const pos = picker.pick_item_position();

            auto i = std::make_unique<fruit>(pos, *this->current_game, 5);

            habitat.add_item(std::move(i));

            ++num_of_spawned_items;
        }
        catch (std::exception const&)
        {
        }
    }
}

void application::create_renderers()
{
    create_world_renderer();

    create_hud_renderer();
}

void application::create_world_renderer()
{
    this->textures = std::make_unique<texture_repository>();

    this->world_drawer = std::make_unique<world_renderer>(this->block_size,
                                                          *this->textures);
}

void application::create_hud_renderer()
{
    this->hud_drawer = std::make_unique<hud_renderer>();
}

void application::setup_perspective_camera()
{
    auto const view = this->auto_follow ? get_auto_follow_camera_view()
                                        : get_camera_view();

    this->camera.setPerspective(60.0f, getWindowAspectRatio(), 5.f, 3000.f);
    
    this->camera.lookAt(view.eye, view.center, view.up);
    
    cinder::gl::setMatrices(this->camera);
}

camera_view application::get_camera_view() const
{
    auto const eye = cinder::Vec3f{0.f, 0.f, this->camera_distance};

    auto const center = cinder::Vec3f::zero();

    auto const up = cinder::Vec3f::yAxis();

    return {eye, center, up};
}

camera_view application::get_auto_follow_camera_view() const
{
    auto& s = this->current_game->get_snake();
        
    auto head = s.get_trail_head();

    auto pos = get_footprint_position(head.step);

    auto const normalized_eye = vec3f_from_point(pos.location).normalized();

    auto const eye = normalized_eye * this->camera_distance;

    auto const center = cinder::Vec3f::zero();

    auto const n = normalized_eye.cross(cinder::Vec3f::xAxis());

    auto const up = (n == cinder::Vec3f::zero()) ? normalized_eye : n;

    return {eye, center, up};
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

void application::setup_keyboard_commands()
{
    setup_action_commands();

    setup_camera_commands();

    setup_option_commands();
}

void application::setup_action_commands()
{
    using cinder::app::KeyEvent;

    auto turn_left_cmd = [this] { turn_snake_left(); };
    this->keyboard_commands[KeyEvent::KEY_a] = turn_left_cmd;
    this->keyboard_commands[KeyEvent::KEY_LEFT] = turn_left_cmd;

    auto turn_right_cmd = [this] { turn_snake_right(); };
    this->keyboard_commands[KeyEvent::KEY_d] = turn_right_cmd;
    this->keyboard_commands[KeyEvent::KEY_RIGHT] = turn_right_cmd;
}

void application::setup_camera_commands()
{
    using cinder::app::KeyEvent;
    
    auto zoom_in_cmd = [this] { this->camera_distance -= get_zoom_step(); };
    this->keyboard_commands[KeyEvent::KEY_w] = zoom_in_cmd;

    auto zoom_out_cmd = [this] { this->camera_distance += get_zoom_step(); };
    this->keyboard_commands[KeyEvent::KEY_s] = zoom_out_cmd;

    this->keyboard_commands[KeyEvent::KEY_SPACE] = [this] 
    {
        this->auto_follow = !(this->auto_follow); 

        if (!this->auto_follow) 
        {
            auto rot = this->camera.getOrientation();
            
            rot = cinder::Quatf{rot.getAxis(), -rot.getAngle()};

            this->arcball.setQuat(rot);
        }
    };
}

void application::setup_option_commands()
{
    using cinder::app::KeyEvent;

    auto toggle_pause_cmd = [this] 
    { 
        this->current_game->toggle_game_pause();
    };

    this->keyboard_commands[KeyEvent::KEY_p] = toggle_pause_cmd;

    auto toggle_show_fps_cmd = [this] 
    { 
        this->hud_drawer->toogle_show_fps(); 
    };

    this->keyboard_commands[KeyEvent::KEY_f] = toggle_show_fps_cmd;
}

void application::draw_frame()
{
    draw_world();

    calculate_current_fps();

    this->hud_drawer->render(this->current_fps,
                             this->current_game->get_score(),
                             this->current_game->is_game_paused(),
                             this->current_game->is_game_over(),
                             this->auto_follow);
}

void application::draw_world()
{
    auto& s = this->current_game->get_snake();

    auto& t = this->current_game->get_terrain();

    this->world_drawer->render(s, t);
}

int application::get_zoom_step() const
{
    return 20;
}

void application::calculate_current_fps()
{
    auto const time = std::chrono::system_clock::now();

    auto const elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        time - this->last_frame_time);

    this->current_fps = 1000.f / elapsed.count();

    this->last_frame_time = time;
}

void application::turn_snake_left() const
{
    auto& s = this->current_game->get_snake();

    return s.turn_left();
}

void application::turn_snake_right() const
{
    auto& s = this->current_game->get_snake();

    return s.turn_right();
}

}

CINDER_APP_NATIVE(snake_overflow::application, ci::app::RendererGl)

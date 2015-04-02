#include "stdafx.hpp"

#include "snake_overflow/application.hpp"
#include "snake_overflow/camera_manipulator.hpp"
#include "snake_overflow/camera_view.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/hud_renderer.hpp"
#include "snake_overflow/position.hpp"
#include "snake_overflow/point_conversion.hpp"
#include "snake_overflow/random_item_position_picker.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/snake_renderer.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/terrain_builder.hpp"
#include "snake_overflow/texture_repository.hpp"
#include "snake_overflow/world_renderer.hpp"
#include "cinder/ImageIo.h"
#include "util/repeat.hpp"
#include <unordered_set>


#include "snake_overflow/fruit.hpp"
#include <memory>


namespace snake_overflow
{

void application::prepareSettings(Settings* const settings)
{
    settings->setWindowSize(1024, 768);

    settings->setFrameRate(30);
}

void application::setup()
{
    create_renderers();

    create_camera_manipulator();

    setup_depth_buffer();

    setup_keyboard_commands();

    create_game();

    spawn_items();

    this->last_frame_time = std::chrono::system_clock::now();
}

void application::update()
{
    if ((getElapsedFrames() % 3 == 0))
    {
        this->current_game->update();
    }
}

void application::draw()
{
    auto const& s = this->current_game->get_snake();

    this->camera_handler->set_camera_matrices(s);
    
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
    this->camera_handler->begin_arcball_drag(e.getPos());
}

void application::mouseDrag(cinder::app::MouseEvent const e)
{
    this->camera_handler->continue_arcball_drag(e.getPos());
}

void application::mouseWheel(cinder::app::MouseEvent const e)
{
    this->camera_handler->zoom(e.getWheelIncrement());
}

void application::create_game()
{
    auto habitat = std::make_unique<terrain>();

    populate_habitat(*habitat);

    auto const snake_origin = point{0, -5, this->cube_side_length / 2};

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

void application::create_camera_manipulator()
{
    this->camera_handler = std::make_unique<camera_manipulator>();
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
    
    this->keyboard_commands[KeyEvent::KEY_w] = [this] 
    { 
        this->camera_handler->zoom(1.f);
    };
    
    this->keyboard_commands[KeyEvent::KEY_s] = [this] 
    { 
        this->camera_handler->zoom(-1.f);
    };

    this->keyboard_commands[KeyEvent::KEY_SPACE] = [this] 
    { 
        this->camera_handler->toggle_auto_follow(); 
    };
}

void application::setup_option_commands()
{
    using cinder::app::KeyEvent;

    this->keyboard_commands[KeyEvent::KEY_p] = [this] 
    { 
        this->current_game->toggle_game_pause();
    };

    this->keyboard_commands[KeyEvent::KEY_f] = [this] 
    { 
        this->hud_drawer->toogle_show_fps(); 
    };
}

void application::draw_frame()
{
    cinder::gl::clear({0.f, 0.f, 0.0f}, true);

    draw_world();

    calculate_current_fps();

    this->hud_drawer->render(this->current_fps,
                             this->current_game->get_score(),
                             this->current_game->is_game_paused(),
                             this->current_game->is_game_over(),
                             this->camera_handler->is_auto_follow_on());
}

void application::draw_world()
{
    auto& s = this->current_game->get_snake();

    auto& t = this->current_game->get_terrain();

    this->world_drawer->render(s, t);
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

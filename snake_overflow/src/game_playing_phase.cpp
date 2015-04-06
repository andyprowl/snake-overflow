#include "stdafx.hpp"

#include "snake_overflow/arcball_camera_manipulator.hpp"
#include "snake_overflow/diet_pill.hpp"
#include "snake_overflow/fruit.hpp"
#include "snake_overflow/game.hpp"
#include "snake_overflow/game_map.hpp"
#include "snake_overflow/game_playing_phase.hpp"
#include "snake_overflow/playing_phase_hud_renderer.hpp"
#include "snake_overflow/keyboard_input_handler.hpp"
#include "snake_overflow/invulnerability_spell.hpp"
#include "snake_overflow/load_driven_terrain_item_filler.hpp"
#include "snake_overflow/probabilistic_item_spawner.hpp"
#include "snake_overflow/random_item_position_picker.hpp"
#include "snake_overflow/snake.hpp"
#include "snake_overflow/snake_renderer.hpp"
#include "snake_overflow/terrain.hpp"
#include "snake_overflow/world_renderer.hpp"

namespace snake_overflow
{

game_playing_phase::game_playing_phase(
    texture_repository const& textures,
    game_map_block_cache const& terrain_block_cache)
    : textures{textures}
    , terrain_block_cache{terrain_block_cache}
    , current_camera_handler{nullptr}
{
    this->last_frame_time = std::chrono::system_clock::now();
}

bool game_playing_phase::is_done() const
{
    return this->current_game->is_game_over;
}

void game_playing_phase::update()
{
    this->current_game->update();
}

void game_playing_phase::draw()
{
    this->current_camera_handler->set_camera_matrices();
    
    draw_frame();
}

void game_playing_phase::on_keyboard_input(cinder::app::KeyEvent e)
{
    this->keyboard_handler->process_keyboard_input(e.getCode());
}

void game_playing_phase::on_mouse_down(cinder::app::MouseEvent e)
{
    if (is_auto_follow_on())
    {
        return;
    }

    this->arcball_camera_handler->begin_arcball_drag(e.getPos());
}

void game_playing_phase::on_mouse_drag(cinder::app::MouseEvent e)
{
    if (is_auto_follow_on())
    {
        return;
    }

    this->arcball_camera_handler->continue_arcball_drag(e.getPos());
}

void game_playing_phase::on_mouse_wheel(cinder::app::MouseEvent e)
{
    this->current_camera_handler->zoom(e.getWheelIncrement());
}

void game_playing_phase::on_resize()
{
    this->current_camera_handler->on_resize();
}

camera_manipulator& game_playing_phase::get_current_manipulator() const
{
    return *(this->current_camera_handler);
}

void game_playing_phase::activate_next_camera_manipulator()
{
    if (this->current_camera_handler == this->arcball_camera_handler.get())
    {
        this->current_camera_handler = this->auto_follow_camera_handler.get();
    }
    else
    {
        align_arcball_manipulator_to_auto_follow_manipulator();

        this->current_camera_handler = this->arcball_camera_handler.get();
    }
}

void game_playing_phase::start_new_game(game_map& map_prototype)
{
    create_game(map_prototype);

    create_renderers();

    create_camera_manipulators();

    create_keyboard_input_handler();

    catch_snake_on_camera();
}

void game_playing_phase::create_renderers()
{
    create_world_renderer();

    create_hud_renderer();
}

void game_playing_phase::create_world_renderer()
{
    auto const block_size = 20.f;

    this->world_drawer = std::make_unique<world_renderer>(
        block_size, 
        this->textures,
        this->terrain_block_cache);

    this->world_drawer->set_current_game(*this->current_game);
}

void game_playing_phase::create_hud_renderer()
{
    this->hud_drawer = std::make_unique<playing_phase_hud_renderer>();
}

void game_playing_phase::create_camera_manipulators()
{
    bool const auto_follow_was_on = is_auto_follow_on();

    this->arcball_camera_handler = 
        std::make_unique<arcball_camera_manipulator>();

    auto const& s = this->current_game->get_snake();

    this->auto_follow_camera_handler = 
        std::make_unique<auto_follow_camera_manipulator>(s);

    this->current_camera_handler = this->arcball_camera_handler.get();

    if (auto_follow_was_on) { activate_next_camera_manipulator(); }
}

void game_playing_phase::create_game(game_map& map_prototype)
{
    auto m = map_prototype.clone();

    auto& t = m->get_terrain();

    auto p = std::make_unique<random_item_position_picker>(t);

    auto const snake_origin = point{0, -5, 10};

    auto const initial_step = pick_random_starting_footprint(*p, t);

    auto body = std::make_unique<snake_body>(t, initial_step, 3);

    auto s = std::make_unique<snake>(std::move(body), "snake6");

    auto is = create_item_spawner(t, std::move(p));

    auto f = create_terrain_filler(std::move(is));

    this->current_game = std::make_unique<game>(std::move(m), 
                                                std::move(s),
                                                std::move(f));

    this->current_game->terrain_filling_interval = 150;
}

footprint game_playing_phase::pick_random_starting_footprint(
    item_position_picker& picker,
    terrain const& habitat) const
{
    while (true)
    {
        auto const initial_snake_position = picker.pick_item_position();

        auto const initial_step = footprint{initial_snake_position.location, 
                                            {initial_snake_position.face, 
                                            canonical_direction::positive_z()}};

        try
        {
            habitat.compute_next_footprint(initial_step);

            return initial_step;
        }
        catch (std::exception const&)
        {
        }
    }
}

std::unique_ptr<item_spawner> game_playing_phase::create_item_spawner(
    terrain& t,
    std::unique_ptr<item_position_picker>&& p) const
{
    auto is = std::make_unique<probabilistic_item_spawner>(t, std::move(p));

    is->register_item_factory([this] (util::value_ref<position> pos)
    {
        return create_fruit(pos);
    }, 90);

    is->register_item_factory([this] (util::value_ref<position> pos)
    {
        return create_diet_pill(pos);
    }, 8);

    is->register_item_factory([this] (util::value_ref<position> pos)
    {
        return create_invulnerability_spell(pos);
    }, 2);

    return std::move(is);
}

std::unique_ptr<item> game_playing_phase::create_fruit(
    util::value_ref<position> pos) const
{
    random_integer_generator generator{};

    auto const nutrition_value = generator.generate(1, 5);

    auto const lifetime = generator.generate(200, 800);

    return std::make_unique<fruit>(pos, 
                                   *this->current_game, 
                                   lifetime, 
                                   nutrition_value);
}

std::unique_ptr<item> game_playing_phase::create_diet_pill(
    util::value_ref<position> pos) const
{
    random_integer_generator generator{};

    auto const lifetime = generator.generate(100, 500);

    return std::make_unique<diet_pill>(pos, *this->current_game, lifetime, 5);
}

std::unique_ptr<item> game_playing_phase::create_invulnerability_spell(
    util::value_ref<position> pos) const
{
    random_integer_generator generator{};

    auto const lifetime = generator.generate(100, 300);

    return std::make_unique<invulnerability_spell>(pos, 
                                                   *this->current_game, 
                                                   lifetime);
}

std::unique_ptr<terrain_item_filler> game_playing_phase::create_terrain_filler(
    std::unique_ptr<item_spawner>&& is) const
{
    auto f = std::make_unique<load_driven_terrain_item_filler>(std::move(is));

    f->set_minimum_load_factor(0.001);

    f->set_maximum_load_factor(0.005);

    return std::move(f);
}

void game_playing_phase::create_keyboard_input_handler()
{
    this->keyboard_handler = std::make_unique<keyboard_input_handler>(
        *this->current_game,
        *this->hud_drawer,
        *this);
}

void game_playing_phase::catch_snake_on_camera()
{
    if (is_auto_follow_on())
    {
        return;
    }

    align_arcball_manipulator_to_auto_follow_manipulator();
}

void game_playing_phase::align_arcball_manipulator_to_auto_follow_manipulator()
{
    this->auto_follow_camera_handler->set_camera_matrices();

    auto const rot = this->auto_follow_camera_handler->get_camera_orientation();

    auto const opposite_rot = cinder::Quatf{rot.getAxis(), -rot.getAngle()};

    this->arcball_camera_handler->set_camera_orientation(opposite_rot);
}

void game_playing_phase::draw_frame()
{
    cinder::gl::clear({0.f, 0.f, 0.0f}, true);

    draw_world();

    calculate_current_fps();
    
    this->hud_drawer->render(this->current_fps,
                             this->current_game->score,
                             this->current_game->is_game_paused,
                             this->current_game->is_game_over,
                             is_auto_follow_on());
}

void game_playing_phase::draw_world()
{
    this->world_drawer->render();
}

void game_playing_phase::calculate_current_fps()
{
    auto const time = std::chrono::system_clock::now();
     
    auto const elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        time - this->last_frame_time);

    this->current_fps = 1000.f / elapsed.count();

    this->last_frame_time = time;
}

bool game_playing_phase::is_auto_follow_on() const
{
    if (this->auto_follow_camera_handler == nullptr)
    {
        return false;
    }

    return (this->current_camera_handler == 
            this->auto_follow_camera_handler.get());
}

}
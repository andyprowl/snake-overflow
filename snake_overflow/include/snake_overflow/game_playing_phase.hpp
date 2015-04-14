#pragma once

#include "snake_overflow/arcball_camera_manipulator.hpp"
#include "snake_overflow/auto_follow_camera_manipulator.hpp"
#include "snake_overflow/camera_manipulator_toggler.hpp"
#include "snake_overflow/interaction_phase.hpp"
#include "util/value_ref.hpp"
#include <boost/optional.hpp>
#include <chrono>
#include <memory>

namespace snake_overflow
{

struct footprint;
struct position;

class application_state_machine;
class game;
class game_map;
class game_map_block_cache;
class high_scores_database;
class high_scores_rankings;
class item;
class playing_phase_hud_renderer;
class item_position_picker;
class item_spawner;
class playing_phase_keyboard_handler;
class playing_phase_sound_player;
class snake;
class terrain;
class terrain_item_filler;
class texture_repository;
class world_renderer;

class game_playing_phase : public interaction_phase
                         , public camera_manipulator_toggler
{

public:

    game_playing_phase(application_state_machine& state_machine,
                       texture_repository const& textures,
                       game_map_block_cache const& terrain_block_cache,
                       high_scores_database& scores);
    
    virtual void update() override;

    virtual void draw() override;

    virtual void on_keyboard_input(cinder::app::KeyEvent e) override;

    virtual void on_mouse_down(cinder::app::MouseEvent e) override;

    virtual void on_mouse_drag(cinder::app::MouseEvent e) override;

    virtual void on_mouse_wheel(cinder::app::MouseEvent e) override;

    virtual void on_resize() override;

    virtual camera_manipulator& get_current_manipulator() const override;

    virtual void activate_next_camera_manipulator() override;

    void start_new_game(game_map& map_prototype);

    void restart_game();

private:

    void create_renderers();

    void create_world_renderer();

    void create_hud_renderer();

    void create_camera_manipulators();

    void create_game(game_map& map_prototype);

    high_scores_rankings& get_rankings_for_map(game_map const& m) const;

    std::unique_ptr<snake> create_snake(item_position_picker& picker,
                                        terrain& t) const;

    footprint pick_random_starting_footprint(item_position_picker& picker,
                                             terrain const& habitat) const;

    std::unique_ptr<item_spawner> create_item_spawner(
        terrain& t,
        std::unique_ptr<item_position_picker>&& p) const;

    std::unique_ptr<item> create_fruit(util::value_ref<position> pos) const;

    std::unique_ptr<item> create_diet_pill(util::value_ref<position> pos) const;

    std::unique_ptr<item> create_invulnerability_potion(
        util::value_ref<position> pos) const;

    std::unique_ptr<item> create_speed_booster(
        util::value_ref<position> pos) const;

    std::unique_ptr<terrain_item_filler> create_terrain_filler(
        std::unique_ptr<item_spawner>&& is) const;
    
    void create_keyboard_input_handler();

    void create_sounds_player();

    void catch_snake_on_camera();

    void align_arcball_manipulator_to_auto_follow_manipulator();

    void draw_frame();

    bool is_auto_follow_on() const;

private:

    application_state_machine& state_machine;

    texture_repository const& textures;

    game_map_block_cache const& terrain_block_cache;

    high_scores_database& high_scores;

    std::unique_ptr<world_renderer> world_drawer;

    std::unique_ptr<playing_phase_hud_renderer> hud_drawer;

    std::unique_ptr<arcball_camera_manipulator> arcball_camera_handler;

    std::unique_ptr<auto_follow_camera_manipulator> auto_follow_camera_handler;

    std::unique_ptr<playing_phase_keyboard_handler> keyboard_handler;
    
    std::unique_ptr<playing_phase_sound_player> sound_player;

    std::unique_ptr<game> current_game;

    camera_manipulator* current_camera_handler = nullptr;

};

}
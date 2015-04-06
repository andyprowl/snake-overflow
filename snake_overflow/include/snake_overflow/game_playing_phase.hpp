#pragma once

#include "snake_overflow/arcball_camera_manipulator.hpp"
#include "snake_overflow/auto_follow_camera_manipulator.hpp"
#include "snake_overflow/camera_manipulator_toggler.hpp"
#include "snake_overflow/interaction_phase.hpp"
#include "snake_overflow/game_over_continuation_option.hpp"
#include <boost/optional.hpp>
#include <chrono>
#include <memory>

namespace snake_overflow
{

struct footprint;
struct position;

class game;
class game_map;
class game_map_block_cache;
class item;
class playing_phase_hud_renderer;
class item_position_picker;
class item_spawner;
class playing_phase_keyboard_handler;
class terrain;
class terrain_item_filler;
class texture_repository;
class world_renderer;

class game_playing_phase : public interaction_phase
                         , public camera_manipulator_toggler
                         , public continuation_option_setter
{

public:

    game_playing_phase(texture_repository const& textures,
                       game_map_block_cache const& terrain_block_cache);

    virtual bool is_done() const override;

    virtual void update() override;

    virtual void draw() override;

    virtual void on_keyboard_input(cinder::app::KeyEvent e) override;

    virtual void on_mouse_down(cinder::app::MouseEvent e) override;

    virtual void on_mouse_drag(cinder::app::MouseEvent e) override;

    virtual void on_mouse_wheel(cinder::app::MouseEvent e) override;

    virtual void on_resize() override;

    virtual camera_manipulator& get_current_manipulator() const override;

    virtual void activate_next_camera_manipulator() override;

    virtual void set_continuation_option(
        game_over_continuation_option option) override;

    void start_new_game(game_map& map_prototype);

    boost::optional<game_over_continuation_option> 
        get_continuation_option() const;

private:

    void create_renderers();

    void create_world_renderer();

    void create_hud_renderer();

    void create_camera_manipulators();

    void create_game(game_map& map_prototype);

    footprint pick_random_starting_footprint(item_position_picker& picker,
                                             terrain const& habitat) const;

    std::unique_ptr<item_spawner> create_item_spawner(
        terrain& t,
        std::unique_ptr<item_position_picker>&& p) const;

    std::unique_ptr<item> create_fruit(util::value_ref<position> pos) const;

    std::unique_ptr<item> create_diet_pill(util::value_ref<position> pos) const;

    std::unique_ptr<item> create_invulnerability_spell(
        util::value_ref<position> pos) const;

    std::unique_ptr<terrain_item_filler> create_terrain_filler(
        std::unique_ptr<item_spawner>&& is) const;
    
    void create_keyboard_input_handler();

    void catch_snake_on_camera();

    void align_arcball_manipulator_to_auto_follow_manipulator();

    void draw_frame();

    void draw_world();

    bool is_auto_follow_on() const;

private:

    texture_repository const& textures;

    game_map_block_cache const& terrain_block_cache;

    std::unique_ptr<world_renderer> world_drawer;

    std::unique_ptr<playing_phase_hud_renderer> hud_drawer;

    std::unique_ptr<arcball_camera_manipulator> arcball_camera_handler;

    std::unique_ptr<auto_follow_camera_manipulator> auto_follow_camera_handler;

    std::unique_ptr<playing_phase_keyboard_handler> keyboard_handler;
    
    std::unique_ptr<game> current_game;

    boost::optional<game_over_continuation_option> continuation_option;

    camera_manipulator* current_camera_handler = nullptr;

};

}
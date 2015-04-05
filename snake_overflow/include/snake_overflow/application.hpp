#pragma once

#include "util/value_ref.hpp"
#include <chrono>
#include <memory>

namespace snake_overflow
{

struct footprint;
struct position;

class camera_manipulator;
class game;
class item;
class hud_renderer;
class item_position_picker;
class item_spawner;
class keyboard_input_handler;
class terrain;
class terrain_item_filler;
class terrain_provider;
class texture_repository;
class world_renderer;

class application : public cinder::app::AppNative 
{
 
private:
    
    virtual void prepareSettings(Settings* settings) override;

    virtual void setup() override;
        
    virtual void update() override;
    
    virtual void draw() override;

    virtual void keyDown(cinder::app::KeyEvent e) override;

    virtual void mouseDown(cinder::app::MouseEvent e) override;

    virtual void mouseDrag(cinder::app::MouseEvent e) override;

    virtual void mouseWheel(cinder::app::MouseEvent e) override;

    virtual void resize() override;

    void create_renderers();

    void create_world_renderer();

    void create_hud_renderer();

    void create_camera_manipulator();

    void setup_depth_buffer();

    void create_terrain_provider();

    void start_new_game();

    void create_game();

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

    void catch_snake_on_camera() const;

    bool try_handle_game_restart_command(cinder::app::KeyEvent e);

    bool try_handle_full_screen_toggling_command(cinder::app::KeyEvent e);

    void toggle_full_screen();

    void draw_frame();

    void draw_world();

    void calculate_current_fps();

private:

    std::unique_ptr<game> current_game;
        
    std::unique_ptr<terrain_provider> habitat_provider;

    std::unique_ptr<texture_repository> textures;

    std::unique_ptr<world_renderer> world_drawer;

    std::unique_ptr<hud_renderer> hud_drawer;

    std::unique_ptr<camera_manipulator> camera_handler;

    std::unique_ptr<keyboard_input_handler> keyboard_handler;

    float block_size = 20.f;

    std::chrono::time_point<std::chrono::system_clock> last_frame_time;

    float current_fps = 60.0;

};

}
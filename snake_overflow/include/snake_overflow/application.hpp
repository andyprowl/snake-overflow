#pragma once

#include "snake_overflow/application_hud_renderer.hpp"
#include "snake_overflow/fps_calculator.hpp"
#include "snake_overflow/game_map_block_cache.hpp"
#include "snake_overflow/game_playing_phase.hpp"
#include "snake_overflow/map_selection_phase.hpp"
#include "util/value_ref.hpp"
#include <memory>

namespace snake_overflow
{

class game_map;
class game_map_repository;
class texture_repository;

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

    void create_game_map_repository();

    void create_texture_repository();

    void create_hud_renderer();

    void create_interaction_phases();

    void setup_depth_buffer();

    void switch_to_playing_phase_if_user_just_chose_map();

    bool try_handle_full_screen_toggling_command(cinder::app::KeyEvent e);

    bool try_handle_game_restart_command(cinder::app::KeyEvent e);

    bool try_handle_map_change_command(cinder::app::KeyEvent e);

    void toggle_full_screen();

    game_map& get_currently_selected_map() const;

private:
        
    std::unique_ptr<game_map_repository> game_maps;

    std::unique_ptr<texture_repository> textures;

    std::unique_ptr<game_playing_phase> playing_phase;

    std::unique_ptr<map_selection_phase> selection_phase;

    std::unique_ptr<application_hud_renderer> hud_renderer;

    fps_calculator current_fps;

    interaction_phase* current_phase = nullptr;

    game_map_block_cache terrain_block_cache;

};

}
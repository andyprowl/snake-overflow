#pragma once

#include "snake_overflow/arcball_camera_manipulator.hpp"
#include "snake_overflow/interaction_phase.hpp"
#include "snake_overflow/selection_phase_hud_renderer.hpp"
#include "snake_overflow/terrain_renderer.hpp"
#include <memory>

namespace snake_overflow
{

class game_map_block_cache;
class game_map_repository;
class texture_repository;

class map_selection_phase : public interaction_phase
{

public:

    map_selection_phase(game_map_repository const& game_maps,
                        texture_repository const& textures,
                        game_map_block_cache const& terrain_block_cache);

    virtual bool is_done() const override;

    virtual void update() override;

    virtual void draw() override;

    virtual void on_keyboard_input(cinder::app::KeyEvent e) override;

    virtual void on_mouse_down(cinder::app::MouseEvent e) override;

    virtual void on_mouse_drag(cinder::app::MouseEvent e) override;

    virtual void on_mouse_wheel(cinder::app::MouseEvent e) override;

    virtual void on_resize() override;

    game_map& get_selected_map() const;

    void invalidate_selection();

private:

    void select_next_map();

    void select_previous_map();

    int get_num_of_available_maps() const;

    void show_selected_map();

    void set_selected_map_in_terrain_renderer();

    void skew_camera();

private:

    game_map_repository const& game_maps;

    texture_repository const& textures;

    game_map_block_cache const& terrain_block_cache;

    std::vector<game_map*> available_maps;

    int selected_map_index;

    bool is_selection_confirmed;

    std::unique_ptr<terrain_renderer> map_renderer;

    arcball_camera_manipulator camera_handler;

    selection_phase_hud_renderer hud_renderer;

};

}
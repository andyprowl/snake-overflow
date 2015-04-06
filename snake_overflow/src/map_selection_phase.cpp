#include "stdafx.hpp"

#include "snake_overflow/game_map_repository.hpp"
#include "snake_overflow/map_selection_phase.hpp"

namespace snake_overflow
{

map_selection_phase::map_selection_phase(
    game_map_repository const& game_maps,
    texture_repository const& textures,
    game_map_block_cache const& terrain_block_cache)
    : game_maps{game_maps}
    , textures{textures}
    , terrain_block_cache{terrain_block_cache}
{
    this->available_maps = this->game_maps.get_all_maps();

    this->map_renderer = std::make_unique<terrain_renderer>(
        20.f, 
        this->textures,
        this->terrain_block_cache); 

    show_selected_map();
}

bool map_selection_phase::is_done() const
{
    return this->selection_confirmed;
}

void map_selection_phase::update()
{
}

void map_selection_phase::draw()
{
    cinder::gl::clear({0.f, 0.f, 0.0f}, true);

    this->camera_handler.set_camera_matrices();
    
    this->map_renderer->render();

    auto& m = get_selected_map();

    this->hud_renderer.render(m.get_name());
}

void map_selection_phase::on_keyboard_input(cinder::app::KeyEvent const e)
{
    switch (e.getCode())
    {
        case cinder::app::KeyEvent::KEY_RIGHT:
        {
            return select_next_map();
        }

        case cinder::app::KeyEvent::KEY_LEFT:
        {
            return select_previous_map();
        }

        case cinder::app::KeyEvent::KEY_RETURN:
        {
            this->selection_confirmed = true;

            break;
        }

        default:
        {
            return;
        }
    }
}

void map_selection_phase::on_mouse_down(cinder::app::MouseEvent const e)
{
    this->camera_handler.begin_arcball_drag(e.getPos());
}

void map_selection_phase::on_mouse_drag(cinder::app::MouseEvent const e)
{
    this->camera_handler.continue_arcball_drag(e.getPos());
}

void map_selection_phase::on_mouse_wheel(cinder::app::MouseEvent const e)
{
    this->camera_handler.zoom(e.getWheelIncrement());
}

void map_selection_phase::on_resize()
{
    this->camera_handler.on_resize();
}

game_map& map_selection_phase::get_selected_map() const
{
    return *(this->available_maps[this->selected_map_index]);
}

void map_selection_phase::select_next_map()
{
    auto const num_of_maps = get_num_of_available_maps();
            
    this->selected_map_index = (this->selected_map_index + 1) % num_of_maps;

    show_selected_map();
}

void map_selection_phase::select_previous_map()
{
    auto const num_of_maps = get_num_of_available_maps();
            
    this->selected_map_index = (this->selected_map_index + 1) % num_of_maps;

    show_selected_map();
}

int map_selection_phase::get_num_of_available_maps() const
{
    return static_cast<int>(this->available_maps.size());
}

void map_selection_phase::show_selected_map()
{
    set_selected_map_in_terrain_renderer();

    skew_camera();
}

void map_selection_phase::set_selected_map_in_terrain_renderer()
{
    auto& m = get_selected_map();

    this->map_renderer->set_current_map(m);
}

void map_selection_phase::skew_camera()
{
    this->camera_handler.reset_camera_zoom();

    this->camera_handler.zoom(-10.f);

    auto const rot = cinder::Quatf{0.78f, 0.78f, 0.78f} * 
                     cinder::Quatf{0.45f, -0.45f, 0.0f};

    this->camera_handler.set_camera_orientation(rot);
}

}
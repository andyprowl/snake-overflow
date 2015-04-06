#include "stdafx.hpp"

#include "snake_overflow/application.hpp"
#include "snake_overflow/game_map_repository.hpp"
#include "snake_overflow/texture_repository.hpp"

namespace snake_overflow
{

void application::prepareSettings(Settings* const settings)
{
    settings->setWindowSize(1024, 768);

    settings->setFrameRate(30);

    settings->setTitle("Snake Overflow");
}

void application::setup()
{
    create_game_map_repository();

    create_texture_repository();

    create_hud_renderer();

    create_interaction_phases();

    setup_depth_buffer();

    setup_keyboard_commands();
}

void application::update()
{
    this->current_fps.update();

    this->current_phase->update();

    if (switch_to_playing_phase_if_user_just_chose_map()) { return; }

    if (restart_or_change_map_if_playing_game_is_over()) { return; }
}

void application::draw()
{
    this->current_phase->draw();

    this->hud_renderer->render(this->current_fps);
}

void application::keyDown(cinder::app::KeyEvent const e)
{
    if (process_keyboard_input(e)) { return; }

    if (switch_to_playing_phase_if_user_just_chose_map()) { return; }

    if (restart_or_change_map_if_playing_game_is_over()) { return; }

    this->current_phase->on_keyboard_input(e);
}

void application::mouseDown(cinder::app::MouseEvent const e)
{
    this->current_phase->on_mouse_down(e);
}

void application::mouseDrag(cinder::app::MouseEvent const e)
{
    this->current_phase->on_mouse_drag(e);
}

void application::mouseWheel(cinder::app::MouseEvent const e)
{
    this->current_phase->on_mouse_wheel(e);
}

void application::resize()
{
    this->current_phase->on_resize();
}

void application::create_game_map_repository()
{
    this->game_maps = std::make_unique<game_map_repository>();
}

void application::create_texture_repository()
{
    this->textures = std::make_unique<texture_repository>();
}

void application::create_hud_renderer()
{
    this->hud_renderer = std::make_unique<application_hud_renderer>();
}

void application::create_interaction_phases()
{
    this->selection_phase = std::make_unique<map_selection_phase>(
        *(this->game_maps),
        *(this->textures),
        this->terrain_block_cache);

    this->playing_phase = std::make_unique<game_playing_phase>(
        *(this->textures),
        this->terrain_block_cache);

    this->current_phase = this->selection_phase.get();
}

void application::setup_depth_buffer()
{
    cinder::gl::enableDepthRead();
    
    cinder::gl::enableDepthWrite();
}

void application::setup_keyboard_commands()
{
    using cinder::app::KeyEvent;
    
    this->keyboard_commands[KeyEvent::KEY_f] = [this] (KeyEvent const)
    { 
        this->hud_renderer->toogle_show_fps(); 

        return true;
    };

    this->keyboard_commands[KeyEvent::KEY_RETURN] = [this] (KeyEvent const e)
    { 
        if (e.isControlDown())
        { 
            toggle_full_screen(); 
            return true; 
        }
        else
        {
            return false;
        }
    };
}

bool application::switch_to_playing_phase_if_user_just_chose_map()
{
    if (is_playing_phase_active())
    {
        return false;
    }

    if (this->selection_phase->is_done())
    {
        auto& selected_map = get_currently_selected_map();

        this->playing_phase->start_new_game(selected_map);

        this->current_phase = this->playing_phase.get();

        return true;
    }

    return false;
}

bool application::restart_or_change_map_if_playing_game_is_over()
{
    if (is_map_selection_phase_active() || !(this->playing_phase->is_done()))
    {
        return false;
    }

    if (this->playing_phase->get_continuation_option() == 
        game_over_continuation_option::change_map)
    {
        this->selection_phase->invalidate_selection();

        this->current_phase = this->selection_phase.get();
    }
    else
    {
        this->playing_phase->start_new_game(get_currently_selected_map());
    }

    return true;
}

bool application::process_keyboard_input(cinder::app::KeyEvent const e)
{
    auto it = this->keyboard_commands.find(e.getCode());
    
    if (it != std::cend(this->keyboard_commands))
    {
        try
        {
            return (it->second)(e);
        }
        catch (std::exception const&)
        {
        }

        return true;
    }

    return false;
}

void application::toggle_full_screen()
{
    auto const full_screen = isFullScreen();
        
    setFullScreen(!full_screen);

    setup_depth_buffer();
}

game_map& application::get_currently_selected_map() const
{
    return this->selection_phase->get_selected_map();
}

bool application::is_playing_phase_active() const
{
    return (this->current_phase == this->playing_phase.get());
}

bool application::is_map_selection_phase_active() const
{
    return (this->current_phase == this->selection_phase.get());
}

}

CINDER_APP_NATIVE(snake_overflow::application, ci::app::RendererGl)

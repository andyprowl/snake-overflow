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

    setup_depth_buffer();

    this->selection_phase = std::make_unique<map_selection_phase>(
        *(this->game_maps),
        *(this->textures),
        this->terrain_block_cache);

    this->playing_phase = std::make_unique<game_playing_phase>(
        *(this->textures),
        this->terrain_block_cache);

    this->current_phase = this->selection_phase.get();
}

void application::update()
{
    if ((this->current_phase == this->selection_phase.get() &&
            this->selection_phase->is_done()))
    {
        this->playing_phase->start_new_game(get_currently_selected_map());

        this->current_phase = this->playing_phase.get();

        return;
    }

    this->current_phase->update();
}

void application::draw()
{
    this->current_phase->draw();
}

void application::keyDown(cinder::app::KeyEvent const e)
{
    if (try_handle_full_screen_toggling_command(e))
    {
        return;
    }

    if (try_handle_game_restart_command(e))
    {
        return;
    }

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

void application::setup_depth_buffer()
{
    cinder::gl::enableDepthRead();
    
    cinder::gl::enableDepthWrite();
}

bool application::try_handle_full_screen_toggling_command(
    cinder::app::KeyEvent const e)
{
    if ((e.getCode() == cinder::app::KeyEvent::KEY_RETURN) && e.isControlDown())
    {
        toggle_full_screen();

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

bool application::try_handle_game_restart_command(
    cinder::app::KeyEvent const e)
{
    if (this->current_phase != this->playing_phase.get())
    {
        return false;
    }

    if (!(this->playing_phase->is_done()))
    {
        return false;
    }
    
    if ((e.getCode() == cinder::app::KeyEvent::KEY_F5) ||
        (e.getCode() == cinder::app::KeyEvent::KEY_RETURN))
    {
        this->playing_phase->start_new_game(get_currently_selected_map());

        return true;
    }

    return false;
}

}

CINDER_APP_NATIVE(snake_overflow::application, ci::app::RendererGl)

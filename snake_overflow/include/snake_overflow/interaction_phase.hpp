#pragma once

namespace snake_overflow
{

class interaction_phase
{

public:

    virtual ~interaction_phase() = default;

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual void on_keyboard_input(cinder::app::KeyEvent e) = 0;

    virtual void on_mouse_down(cinder::app::MouseEvent e) = 0;

    virtual void on_mouse_drag(cinder::app::MouseEvent e) = 0;

    virtual void on_mouse_wheel(cinder::app::MouseEvent e) = 0;

    virtual void on_resize() = 0;

};

}
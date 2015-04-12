#pragma once

namespace snake_overflow
{
    
inline cinder::Vec2f get_screen_resolution()
{
   auto const hDesktop = ::GetDesktopWindow();

   auto desktop = RECT{};
   GetWindowRect(hDesktop, &desktop);

   return {desktop.right, desktop.bottom};
}

}
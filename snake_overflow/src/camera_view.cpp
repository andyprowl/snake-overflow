#include "stdafx.hpp"

#include "snake_overflow/camera_view.hpp"

namespace snake_overflow
{

camera_view::camera_view(util::value_ref<cinder::Vec3f> eye,
                         util::value_ref<cinder::Vec3f> center,
                         util::value_ref<cinder::Vec3f> up)
    : eye{eye}
    , center{center}
    , up{up}
{
}


}
#pragma once

#include "util/value_ref.hpp"

namespace snake_overflow
{

struct camera_view
{

public:

    camera_view(util::value_ref<cinder::Vec3f> eye,
                util::value_ref<cinder::Vec3f> center,
                util::value_ref<cinder::Vec3f> up);

public:

    cinder::Vec3f eye;

    cinder::Vec3f center;

    cinder::Vec3f up;

};

}
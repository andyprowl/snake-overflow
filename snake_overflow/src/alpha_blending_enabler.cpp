#include "stdafx.hpp"

#include "snake_overflow/alpha_blending_enabler.hpp"

namespace snake_overflow
{

alpha_blending_enabler::alpha_blending_enabler(bool const enable)
    : disable_on_destruction{!enable}
{
    if (enable)
    {
        cinder::gl::enableAlphaBlending();
    }
}

alpha_blending_enabler::alpha_blending_enabler(alpha_blending_enabler&& rhs)
    : disable_on_destruction{rhs.disable_on_destruction}
{
    rhs.disable_on_destruction = false;
}

alpha_blending_enabler& alpha_blending_enabler::operator = (
    alpha_blending_enabler&& rhs)
{
    this->disable_on_destruction = rhs.disable_on_destruction;

    rhs.disable_on_destruction = false;

    return *this;
}

alpha_blending_enabler::~alpha_blending_enabler()
{
    if (this->disable_on_destruction)
    {
        cinder::gl::disableAlphaBlending();
    }
}

}
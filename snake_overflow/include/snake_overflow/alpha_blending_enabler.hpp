#pragma once

namespace snake_overflow
{

struct alpha_blending_enabler
{

public:

    alpha_blending_enabler(bool enable);

    alpha_blending_enabler(alpha_blending_enabler const&) = delete;

    alpha_blending_enabler(alpha_blending_enabler&& rhs);

    alpha_blending_enabler& operator = (alpha_blending_enabler const&) = delete;

    alpha_blending_enabler& operator = (alpha_blending_enabler&& rhs);

    ~alpha_blending_enabler();

private:

    bool disable_on_destruction = false;

};

}
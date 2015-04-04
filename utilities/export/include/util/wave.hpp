#pragma once

namespace util
{

inline float wave(float const x, float const minimum, float const maximum)
{
    auto const normalized_wave = (std::sin(x) + 1.f) / 2.f;

    return minimum + normalized_wave * (maximum - minimum);
}

}
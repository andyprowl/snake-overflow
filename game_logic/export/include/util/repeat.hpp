#pragma once

namespace util
{

template<typename F>
void repeat(int const n, F&& f)
{
    for (auto i = 0; i < n; ++i)
    {
        (std::forward<F>(f))();
    }
}

}
#pragma once

#include <utility>

inline constexpr std::pair<int, int> GetStageRatio(int stage) noexcept
{
    if (stage <= 6)
    {
        return { 2, 8 - stage };
    }
    return { stage - 4, 2 };
}

inline constexpr std::pair<int, int> GetAccuracyStageRatio(int stage) noexcept
{
    if (stage <= 6)
    {
        return { 6, 18 - (stage * 2) };
    }
    return { 6 + ((stage - 6) * 2), 6 };
}
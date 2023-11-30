#pragma once

template <typename T>
inline T lerp(const T& a, const T& b, float t)
{
    // Is t within the range [0, 1]
    t = std::max(0.0f, std::min(1.0f, t));

    // Linear interpolation
    return a + (b - a) * t;
}
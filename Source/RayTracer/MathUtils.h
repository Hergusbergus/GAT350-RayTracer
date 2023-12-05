#pragma once
#include <glm/glm.hpp>

template <typename T>
inline T lerp(const T& a, const T& b, float t)
{
    // Is t within the range [0, 1]
    t = std::max(0.0f, std::min(1.0f, t));

    // Linear interpolation
    return a + (b - a) * t;
}

inline glm::vec3 cross(const glm::vec3& v1, const glm::vec3& v2)
{
    return glm::vec3(
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    );
}

inline float dot(const glm::vec3& v1, const glm::vec3& v2) { return glm::dot(v1, v2); }

inline glm::vec3 reflect(const glm::vec3& v, const glm::vec3& n) { return glm::reflect(v, n); }
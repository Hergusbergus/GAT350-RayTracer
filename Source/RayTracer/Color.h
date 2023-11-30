#pragma once
#include <glm/glm.hpp>

// Define color types
using color3_t = glm::vec3;  // Represents RGB with floating point values (0.0-1.0)
using color4_t = glm::vec4;  // Represents RGBA with floating point values (0.0-1.0)
using rgba_t = uint32_t;     // Represents RGBA with integer values

inline color4_t RGBAToColor(const rgba_t& rgba)
{
    float red   = static_cast<float>((rgba >> 24) & 0xFF) / 255.0f;
    float green = static_cast<float>((rgba >> 16) & 0xFF) / 255.0f;
    float blue  = static_cast<float>((rgba >> 8) & 0xFF) / 255.0f;
    float alpha = static_cast<float>(rgba & 0xFF) / 255.0f;

    return color4_t(red, green, blue, alpha);
}

inline rgba_t ColorToRGBA(const color4_t& color)
{
    // Convert
    uint8_t red = static_cast<uint8_t>(color.r * 255.0f);
    uint8_t green = static_cast<uint8_t>(color.g * 255.0f);
    uint8_t blue = static_cast<uint8_t>(color.b * 255.0f);
    uint8_t alpha = static_cast<uint8_t>(color.a * 255.0f);

    // Pack components
    return  (static_cast<uint32_t>(red) << 24)      |
            (static_cast<uint32_t>(green) << 16)    |
            (static_cast<uint32_t>(blue) << 8)      |
            static_cast<uint32_t>(alpha);
}
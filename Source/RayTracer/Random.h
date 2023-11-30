#pragma once
#include <iostream>

void seedRandom(unsigned int seed) { std::srand(seed); }

float random01() { return static_cast<float>(std::rand()) / RAND_MAX; }

float random(float min, float max)
{
    if (min > max) { std::swap(min, max); }

    float randomValue01 = random01();
    return min + randomValue01 * (max - min);
}
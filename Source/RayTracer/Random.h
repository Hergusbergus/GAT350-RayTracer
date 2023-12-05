#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/random.hpp>

inline void seedRandom(unsigned int seed) { std::srand(seed); }

inline float random01() { return static_cast<float>(std::rand()) / RAND_MAX; }

inline float random(float min, float max)
{
    if (min > max) { std::swap(min, max); }

    float randomValue01 = random01();
    return min + randomValue01 * (max - min);
}

inline glm::vec3 random(const glm::vec3& min, const glm::vec3& max)
{
    return glm::vec3(
        glm::linearRand(min.x, max.x),
        glm::linearRand(min.y, max.y),
        glm::linearRand(min.z, max.z)
    );
}

inline glm::vec3 randomInUnitSphere()
{
	glm::vec3 v;
	// generate random vectors between -1 <-> +1, return vector if length is less than 1
	do
	{
        v = glm::linearRand(glm::vec3(-1.0f), glm::vec3(1.0f));
	} while (glm::length2(v) >= 1.0f);

		return v;
}
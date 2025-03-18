#include "Pch.h"

#include "Random.h"

#include <glm/gtc/random.hpp>

namespace PathTracing
{

    float Random::randomFloat()
    {
        return range(0.0f, 1.0f);
    }

    float Random::range(float min, float max)
    {
        return glm::linearRand(min, max);
    }

    glm::vec3 Random::unitSphereVector()
    {
        glm::vec3 v;
        v.x = randomFloat();
        v.y = randomFloat();
        v.z = randomFloat();
        return glm::normalize(v);
    }

}

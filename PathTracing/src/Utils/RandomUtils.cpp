#include "RandomUtils.h"

#include <glm/gtc/random.hpp>

namespace PathTracing
{

namespace Utils
{

double randomDouble(double min, double max)
{
    // Returns a random real in [min, max].
//    return min + (max-min)*random_double();
    return glm::linearRand(min, max);
}

double randomDouble()
{
    // Returns a random real in [0.0, 1.0].
    return randomDouble(0.0f, 1.0f);
}

int randomInt(int min, int max)
{ // Returns a random int in [min, max].
//    double random = randomDouble(min, max+1);
//    int res = static_cast<int>(random);
//    return res;
    return glm::linearRand<int>(min, max);
}

}

}
